//
//  RemoveObjectSimulation.h
//  Testbed
//
//  Created by Tayfun Ateş on 1.10.2019.
//

#ifndef RemoveObjectSimulation_h
#define RemoveObjectSimulation_h

#include "SimulationColor.h"
#include "SimulationObject.h"
#include "Box2D/Extension/b2VisBody.hpp"
#include "Box2D/Extension/b2VisPolygonShape.hpp"
#include "RemoveObjectSimulationSettings.h"
#include <iostream>
#include "JSONHelper.h"
#include "SceneState.h"
#include "SimulationBase.h"

namespace svqa
{
    class RemoveObjectSimulation : public SimulationBase
    {
    public:
        typedef std::shared_ptr<RemoveObjectSimulation> Ptr;
        
        enum SimulationState
        {
            SS_CREATE_SCENE = 0,
            SS_CREATE_FINAL_UNSTABLE = 1,
            SS_CREATE_FINAL_STABLE = 2,
            SS_SEGMENTATION_SCREENSHOT = 3
        };
        
        RemoveObjectSimulation(RemoveObjectSimulationSettings::Ptr _settings_) : SimulationBase(_settings_)
        {
            m_nNumberOfObjects = _settings_->numberOfObjects;
            m_nSimulationState = SS_CREATE_SCENE;
            m_nDistinctMaterialsUsed = 2;
            m_nDistinctObjectsUsed = 2;
            m_vInitialDropVelocity = b2Vec2(0.0f, -20.0f);
            
            SimulationObject largestObject(SimulationObject::BIG_CUBE);
            
            m_vThrowMin = b2Vec2(-10.0f, 20.0f);
            m_vThrowMax = b2Vec2(-5.0f, 40.0f);
            
            {
                b2BodyDef bd;
                b2Body* ground = m_world->CreateBody(&bd);

                b2EdgeShape shape;
                shape.Set(b2Vec2(-40.0f, 0.0f), b2Vec2(40.0f, 0.0f));
                ground->CreateFixture(&shape, 0.0f);
            }
            
            SET_FILE_OUTPUT_TRUE(m_pSettings->outputFilePath)
        }

        virtual void Step(SettingsBase* settings) override
        {
            const bool stable = isSceneStable();
            const bool addObject = stable && m_nNumberOfObjects>0;
            const bool terminateSimulation = m_nNumberOfObjects<=0 && stable;
            
            if(addObject) {
                addSimulationObject();
                m_nNumberOfObjects--;
            }
            
            Simulation::Step(settings);
            
            if(terminateSimulation)
            {
                //state.saveToJSONFile(m_world, "scene.json");
                FINISH_SIMULATION
            }
        }
        
        virtual SimulationID getIdentifier() override
        {
            return SimulationID::ID_RemoveObject;
        }
        
    private:
        int m_nNumberOfObjects;
        SimulationState m_nSimulationState;
        b2Vec2 m_vThrowMin;
        b2Vec2 m_vThrowMax;
        b2Vec2 m_vInitialDropVelocity;
        unsigned short m_nDistinctMaterialsUsed;
        unsigned short m_nDistinctObjectsUsed;
        SceneState state;

        void addSimulationObject()
        {
            float posX = RandomFloat(m_vThrowMin.x, m_vThrowMax.x);
            float posY = RandomFloat(m_vThrowMin.y, m_vThrowMax.y);
            
            int objectIndex = randWithBound(m_nDistinctObjectsUsed);
            SimulationObject object = SimulationObject((SimulationObject::TYPE) objectIndex);
        
            b2VisPolygonShape shape = object.getShape();
            
            int materialIndex = randWithBound(m_nDistinctMaterialsUsed);
            SimulationMaterial mat = SimulationMaterial((SimulationMaterial::TYPE) materialIndex);
            
            b2BodyDef bd;
            bd.type = b2_dynamicBody;
            bd.position = b2Vec2(posX, posY);
            bd.linearVelocity = m_vInitialDropVelocity;
            BODY* body = (BODY*) m_world->CreateBody(&bd);
            body->CreateFixture(&shape, mat.getDensity());
            
    #if !USE_DEBUG_DRAW
            int colorIndex = randWithBound(m_nDistinctColorUsed);
            SimulationColor col = SimulationColor((SimulationColor::TYPE) colorIndex);
            body->setTexture(mat.getTexture());
            body->setColor(col.GetColor(mat.type));
            
            state.add(ObjectState(body, mat.type, col.type, object.type));
    #endif
        }
    };
}

#endif /* RemoveObjectSimulation_h */
