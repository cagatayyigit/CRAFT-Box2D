//
//  ObstructedPathSimulation.h
//  Testbed
//
//  Created by Tayfun Ateş on 24.11.2019.
//

#ifndef ObstructedPathSimulation_h
#define ObstructedPathSimulation_h

#include "SimulationColor.h"
#include "ObstructedPathSettings.h"
#include "SimulationBase.h"
#include "Box2D/Extension/b2VisBody.hpp"
#include "Box2D/Extension/b2VisPolygonShape.hpp"
#include <math.h>

namespace svqa {
    class ObstructedPathSimulation : public SimulationBase
    {
    public:
        typedef std::shared_ptr<ObstructedPathSimulation> Ptr;
        
        ObstructedPathSimulation(ObstructedPathSettings::Ptr _settings_) : SimulationBase(_settings_)
        {
            m_nNumberOfObjects = _settings_->numberOfObjects;
            m_nNumberOfObstacles = _settings_->numberOfObstacles;
            
            m_vInitialDropVelocity = b2Vec2(0.0f, -20.0f);
            
            m_vThrowMin = b2Vec2(-30.0f, 50.0f);
            m_vThrowMax = b2Vec2(30.0f, 50.0f);
            
            m_vObstacleMin = b2Vec2(-30.0f, 10.0f);
            m_vObstacleMax = b2Vec2(30.0f, 40.0f);
            
            m_bObstaclesCreated = false;
            createBoundaries();
            
            SET_FILE_OUTPUT_TRUE(m_pSettings->outputFilePath)
        }

        virtual void Step(SettingsBase* settings) override
        {
            if(!m_bObstaclesCreated) {
                //Obstacles are created in step since it requires GL context to be initialized
                createObstacles();
            }
            
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
                 state.saveToJSONFile(m_world, "scene.json");
                 FINISH_SIMULATION
             }
        }
        
        virtual SimulationID getIdentifier() override
        {
            return SimulationID::ID_ObstructedPath;
        }
        
    private:
        
        void createObstacles()
        {
            for(int i=0; i < m_nNumberOfObstacles; i++) {
                while(!createObstacle()) {
                    
                }
            }
            m_bObstaclesCreated = true;
        }
        
        bool createObstacle()
        {
            SimulationObject object = SimulationObject(SimulationObject::STANDARD_RECTANGLE);
            b2VisPolygonShape shape = object.getShape();
            
            float posX = RandomFloat(m_vObstacleMin.x, m_vObstacleMax.x);
            float posY = RandomFloat(m_vObstacleMin.y, m_vObstacleMax.y);
            float orientation = RandomFloat(-M_PI / 4, M_PI / 4);
            
            SimulationMaterial mat = SimulationMaterial(SimulationMaterial::METAL);
            
            b2BodyDef bd;
            bd.type = b2_dynamicBody;
            bd.position = b2Vec2(posX,posY);
            bd.angle = orientation;
            
            BODY* dynamicObstacle = (BODY*) m_world->CreateBody(&bd);
            dynamicObstacle->CreateFixture(&shape, mat.getDensity());
            m_world->Step(0.0f, 0, 0);
            
            b2ContactEdge* contact = dynamicObstacle->GetContactList();
            if(contact) {
                m_world->DestroyBody(dynamicObstacle);
                return false;
            } else {
                m_world->DestroyBody(dynamicObstacle);
                b2BodyDef bd;
                bd.type = b2_staticBody;
                bd.position = b2Vec2(posX,posY);
                bd.angle = orientation;
                
                BODY* staticObstacle = (BODY*) m_world->CreateBody(&bd);
                staticObstacle->CreateFixture(&shape, mat.getDensity());
                
                int colorIndex = randWithBound(m_nDistinctColorUsed);
                SimulationColor col = SimulationColor((SimulationColor::TYPE) colorIndex);
                staticObstacle->setTexture(mat.getTexture());
                staticObstacle->setColor(col.GetColor(mat.type));
                
                state.add(ObjectState(staticObstacle, mat.type, col.type, object.type));
            }
            return true;
        }
        
        void createBoundaries()
        {
            std::vector<std::pair<b2Vec2, b2Vec2>> boundaries;
            boundaries.push_back(std::make_pair(b2Vec2(-40.0f, 0.0f), b2Vec2(40.0f, 0.0f)));
            boundaries.push_back(std::make_pair(b2Vec2(-30.0f, 0.0f), b2Vec2(-30.0f, 50.0f)));
            boundaries.push_back(std::make_pair(b2Vec2(30.0f, 0.0f), b2Vec2(30.0f, 50.0f)));
            
            for(auto&& bound: boundaries) {
                b2BodyDef bd;
                b2Body* boundBody = m_world->CreateBody(&bd);

                b2EdgeShape shape;
                shape.Set(bound.first, bound.second);
                boundBody->CreateFixture(&shape, 0.0f);
            }
        }
        
        bool m_bObstaclesCreated;
        int m_nNumberOfObjects;
        int m_nNumberOfObstacles;
        b2Vec2 m_vThrowMin;
        b2Vec2 m_vThrowMax;
        b2Vec2 m_vObstacleMin;
        b2Vec2 m_vObstacleMax;
        b2Vec2 m_vInitialDropVelocity;
        
        const std::vector<SimulationObject::TYPE> m_vSimulationObjectTypes = {SimulationObject::SMALL_CUBE, SimulationObject::BIG_CUBE, SimulationObject::SMALL_HEXAGON, SimulationObject::BIG_HEXAGON,
            SimulationObject::SMALL_TRIANGLE, SimulationObject::BIG_TRIANGLE };
        
        SceneState state;

        void addSimulationObject()
        {
            float posX = RandomFloat(m_vThrowMin.x, m_vThrowMax.x);
            float posY = RandomFloat(m_vThrowMin.y, m_vThrowMax.y);
            
            int objectIndex = randWithBound(m_vSimulationObjectTypes.size());
            SimulationObject object = SimulationObject(m_vSimulationObjectTypes[objectIndex]);
        
            b2VisPolygonShape shape = object.getShape();
            
            SimulationMaterial mat = SimulationMaterial(SimulationMaterial::RUBBER);
            
            b2BodyDef bd;
            bd.type = b2_dynamicBody;
            bd.position = b2Vec2(posX, posY);
            bd.linearVelocity = m_vInitialDropVelocity;
            BODY* body = (BODY*) m_world->CreateBody(&bd);
            body->CreateFixture(&shape, mat.getDensity());
            
            int colorIndex = randWithBound(m_nDistinctColorUsed);
            SimulationColor col = SimulationColor((SimulationColor::TYPE) colorIndex);
            body->setTexture(mat.getTexture());
            body->setColor(col.GetColor(mat.type));
            
            state.add(ObjectState(body, mat.type, col.type, object.type));
        }
    };
}

#endif /* ObstructedPathSimulation_h */
