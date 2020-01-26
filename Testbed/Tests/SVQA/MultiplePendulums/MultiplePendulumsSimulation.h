//
//  MultiplePendulumsSimulation.h
//  Testbed
//
//  Created by Tayfun Ateş on 11.01.2020.
//

#ifndef MultiplePendulumsSimulation_h
#define MultiplePendulumsSimulation_h

#include "SimulationColor.h"
#include "MultiplePendulumsSettings.h"
#include "SimulationBase.h"
#include "Box2D/Extension/b2VisBody.hpp"
#include "Box2D/Extension/b2VisPolygonShape.hpp"

namespace svqa {
    class MultiplePendulumsSimulation : public SimulationBase
    {
    public:
        typedef std::shared_ptr<MultiplePendulumsSimulation> Ptr;
        
        struct PendulumInfo
        {
            BODY* pendulum;
            BODY* anchor;
        };
        
        MultiplePendulumsSimulation(MultiplePendulumsSettings::Ptr _settings_) : SimulationBase(_settings_)
        {
            m_bInitialSceneCreated = false;
            m_bCreatedPendulums = false;
            
            m_nNumberOfObjects = _settings_->numberOfObjects;
            m_nNumberOfPendulums = _settings_->numberOfPendulums;
            
            m_vInitialDropVelocity = b2Vec2(0.0f, -20.0f);
            
            m_vThrowMin = b2Vec2(0.0f, 50.0f);
            m_vThrowMax = b2Vec2(0.0f, 50.0f);
            
            m_vPendulumRelativeRange = b2Vec2(-10.0f, 10.0f);
            m_vXPosBoundaries = b2Vec2(-25.0f, 25.0f);
            
            createBoundaries();
            
            SET_FILE_OUTPUT_TRUE(m_pSettings->outputFilePath)
        }

        virtual void Step(SettingsBase* settings) override
        {
            if(!m_bInitialSceneCreated) {
                createImmediateInitialScene(m_nNumberOfObjects, m_vSimulationObjectTypes, m_vThrowMin, m_vThrowMax, m_vInitialDropVelocity);
                m_bInitialSceneCreated=true;
            }
            
            if(!m_bCreatedPendulums) {
                createPendulums();
                m_bCreatedPendulums=true;
            }
            
            const bool stable = isSceneStable();
            const bool terminateSimulation = (m_bInitialSceneCreated && m_bCreatedPendulums && stable);

            Simulation::Step(settings);

            if(terminateSimulation)
            {
                state.saveToJSONFile(m_world, "scene.json");
                FINISH_SIMULATION
            }
        }
        
        virtual SimulationID getIdentifier() override
        {
            return SimulationID::ID_MultiplePendulums;
        }
        
    private:
    
        void createPendulums()
        {
            std::vector<PendulumInfo> res;
            while(1) {
                float relativePos = RandomFloat(m_vPendulumRelativeRange.x, m_vPendulumRelativeRange.y);
                const float& pinPos = RandomFloat(m_vXPosBoundaries.x, m_vXPosBoundaries.y);
                bool safe = true;
                for(size_t p=0; p<res.size();p++) {
                    PendulumInfo currentPendulumInfo = res[p];
                    if(fabs(pinPos - currentPendulumInfo.anchor->GetPosition().x)<10.0f) {
                        safe = false;
                        break;
                    }
                }
                
                if(safe) {
                    PendulumInfo newPendulumInfo = createPendulum(pinPos, relativePos);
                    res.push_back(newPendulumInfo);
                    
                }
                
                if(res.size() >= m_nNumberOfPendulums) {
                    break;
                }
            }
        }
        
        PendulumInfo createPendulum(const float& xPinPos, const float& xPendulumRelativePos)
        {
            BODY* pin = nullptr;
            BODY* pendulum = nullptr;
            
            const float y = 15.0f;
            const float yDiff = 10.0f;
            
            int colorIndex = randWithBound(m_nDistinctColorUsed);
            SimulationColor col = SimulationColor((SimulationColor::TYPE) colorIndex);
            SimulationMaterial mat = SimulationMaterial(SimulationMaterial::RUBBER);
            
            {
                SimulationObject object = SimulationObject(SimulationObject::WALL_PIN);
                ShapePtr shape = object.getShape();
                
                b2BodyDef bd;
                bd.angle = M_PI / 4;
                bd.type = b2_staticBody;
                //bd.position = b2Vec2(pinPosition.x+pinOffset.x,pinPosition.y+yOffset);
                bd.position = b2Vec2(xPinPos, y);
                
                pin = (BODY*) m_world->CreateBody(&bd);
                
                b2FixtureDef fd;
                fd.shape = shape.get();
                fd.density = mat.getDensity();
                fd.friction = 0.2f;
                pin->CreateFixture(&fd);
                
                pin->setColor(col.GetColor());
            }
            
            {
                SimulationObject pendulumBody = SimulationObject(SimulationObject::BIG_CIRCLE);
                b2CircleShape pendulumBodyShape = *(std::static_pointer_cast<b2CircleShape>(pendulumBody.getShape()));
                
                b2FixtureDef fd;
                fd.shape = &pendulumBodyShape;
                fd.friction = 0.2f;
                fd.filter.categoryBits = 0x0001;
                fd.filter.maskBits = 0xFFFF & ~0x0002;
                fd.density = 100.0f;
                fd.filter.categoryBits = 0x0002;
                
                b2BodyDef bd;
                bd.type = b2_dynamicBody;
                bd.position.Set(xPinPos+xPendulumRelativePos, y);
                bd.angularDamping = 0.4f;
                bd.linearDamping = 0.3f;
                
                pendulum = (BODY*) m_world->CreateBody(&bd);
                pendulum->CreateFixture(&fd);
                pendulum->setColor(col.GetColor());
            }
            
            b2RopeJointDef jd;
            jd.maxLength = yDiff;
            jd.collideConnected = true;
            b2Vec2 p1, p2, d;
            
            jd.bodyA = pin;
            jd.bodyB = pendulum;
            jd.localAnchorA.Set(0.0f, 0.0f);
            jd.localAnchorB.Set(0.0f, 0.0f);;
            p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
            p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
            d = p2 - p1;
            b2Joint* joint = m_world->CreateJoint(&jd);
        
            
            PendulumInfo res;
            res.pendulum = pendulum;
            res.anchor = pin;
            return res;
        }
        
        bool m_bCreatedPendulums;
        bool m_bInitialSceneCreated;
        int m_nNumberOfObjects;
        int m_nNumberOfPendulums;
        b2Vec2 m_vThrowMin;
        b2Vec2 m_vThrowMax;
        b2Vec2 m_vInitialDropVelocity;

        b2Vec2 m_vPendulumRelativeRange;
        b2Vec2 m_vXPosBoundaries;
        
        const std::vector<SimulationObject::TYPE> m_vSimulationObjectTypes = {SimulationObject::SMALL_CUBE, SimulationObject::BIG_CUBE, SimulationObject::SMALL_HEXAGON, SimulationObject::BIG_HEXAGON};
        
        SceneState state;
    };
}


#endif /* MultiplePendulumsSimulation_h */
