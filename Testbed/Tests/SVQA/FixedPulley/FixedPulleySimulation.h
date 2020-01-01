//
//  FixedPulleySimulation.h
//  Testbed
//
//  Created by Tayfun Ateş on 27.11.2019.
//

#ifndef FixedPulleySimulation_h
#define FixedPulleySimulation_h

#include "SimulationColor.h"
#include "FixedPulleySettings.h"
#include "SimulationBase.h"
#include "Box2D/Extension/b2VisBody.hpp"
#include "Box2D/Extension/b2VisPolygonShape.hpp"

namespace svqa {
    class FixedPulleySimulation : public SimulationBase
    {
    public:
        typedef std::shared_ptr<FixedPulleySimulation> Ptr;
        
        FixedPulleySimulation(FixedPulleySettings::Ptr _settings_) : SimulationBase(_settings_)
        {
            m_bInitialSceneCreated = false;
            m_nNumberOfObjects = _settings_->numberOfObjects;
            
            m_vInitialDropVelocity = b2Vec2(0.0f, -20.0f);
            
            m_vThrowMin = b2Vec2(0.0f, 50.0f);
            m_vThrowMax = b2Vec2(0.0f, 50.0f);
            
            createBoundaries();
            
            SET_FILE_OUTPUT_TRUE(m_pSettings->outputFilePath)
        }

        virtual void Step(SettingsBase* settings) override
        {
            if(!m_bInitialSceneCreated) {
                createImmediateInitialScene(m_nNumberOfObjects, m_vSimulationObjectTypes, m_vThrowMin, m_vThrowMax, m_vInitialDropVelocity);
                m_bInitialSceneCreated=true;
            }
            
            if(!m_bCreatedPulley) {
                createPulley();
                m_bCreatedPulley=true;
            }
            
            const bool stable = isSceneStable();
            const bool terminateSimulation = (m_bInitialSceneCreated && m_bCreatedPulley && stable);

            Simulation::Step(settings);

            if(terminateSimulation)
            {
                state.saveToJSONFile(m_world, "scene.json");
                FINISH_SIMULATION
            }
        }
        
        virtual SimulationID getIdentifier() override
        {
            return SimulationID::ID_FixedPulley;
        }
        
    private:
        
        void createPulley()
        {
            b2BodyDef bd;

            float32 y = 16.0f;
            float32 L = 24.0f;
            
            {
                b2EdgeShape edge;
                edge.Set(b2Vec2(-40.0f, 0.0f), b2Vec2(40.0f, 0.0f));
                
                SimulationObject object = SimulationObject(SimulationObject::SMALL_CIRCLE);
                b2CircleShape circle = *(std::static_pointer_cast<b2CircleShape>(object.getShape()));
                
                SimulationMaterial mat = SimulationMaterial(SimulationMaterial::METAL);
                SimulationColor col = SimulationColor(SimulationColor::GRAY);
                
                b2BodyDef bd;
                bd.type = b2_staticBody;
                
                circle.m_p.Set(-10.0f, y + L);
                BODY* circleBody = (BODY*) m_world->CreateBody(&bd);
                circleBody->CreateFixture(&circle, 0.0f);
                circleBody->setTexture(mat.getTexture());
                circleBody->setColor(col.GetColor());
                
                circle.m_p.Set(10.0f, y + L);
                circleBody = (BODY*) m_world->CreateBody(&bd);
                circleBody->CreateFixture(&circle, 0.0f);
                circleBody->setTexture(mat.getTexture());
                circleBody->setColor(col.GetColor());
            }
            
            {
                SimulationMaterial mat1 = SimulationMaterial(SimulationMaterial::RUBBER);
                SimulationMaterial mat2 = SimulationMaterial(SimulationMaterial::METAL);
                
                int colorIndex = randWithBound(m_nDistinctColorUsed);
                SimulationColor col = SimulationColor((SimulationColor::TYPE) colorIndex);
                
                SimulationObject object = SimulationObject(SimulationObject::STANDARD_RECTANGLE);
                ShapePtr shape = object.getShape();

                b2BodyDef bd;
                bd.type = b2_dynamicBody;

                bd.position.Set(-10.0f, y);
                BODY* body1 = (BODY*) m_world->CreateBody(&bd);
                body1->CreateFixture(shape.get(), mat1.getDensity());

                bd.position.Set(10.0f, y);
                BODY* body2 = (BODY*) m_world->CreateBody(&bd);
                body2->CreateFixture(shape.get(), mat2.getDensity());
                
                body1->setTexture(mat1.getTexture());
                body1->setColor(col.GetColor());
                body2->setTexture(mat2.getTexture());
                body2->setColor(col.GetColor());

                b2PulleyJointDef pulleyDef;
                b2Vec2 anchor1(-10.0f, y);
                b2Vec2 anchor2(10.0f, y);
                b2Vec2 groundAnchor1(-10.0f, y + L);
                b2Vec2 groundAnchor2(10.0f, y + L);
                pulleyDef.Initialize(body1, body2, groundAnchor1, groundAnchor2, anchor1, anchor2, 1.5f);
            
                (b2PulleyJoint*)m_world->CreateJoint(&pulleyDef);
            }
        }
        
        bool m_bCreatedPulley;
        bool m_bInitialSceneCreated;
        int m_nNumberOfObjects;
        b2Vec2 m_vThrowMin;
        b2Vec2 m_vThrowMax;
        b2Vec2 m_vInitialDropVelocity;
        
        const std::vector<SimulationObject::TYPE> m_vSimulationObjectTypes = {SimulationObject::SMALL_CUBE, SimulationObject::BIG_CUBE, SimulationObject::SMALL_HEXAGON, SimulationObject::BIG_HEXAGON,
            SimulationObject::SMALL_TRIANGLE, SimulationObject::BIG_TRIANGLE};
        
        SceneState state;
    };
}

#endif /* FixedPulleySimulation_h */
