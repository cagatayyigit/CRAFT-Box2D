//
//  ConnectedCarsSimulation.h
//  Testbed
//
//  Created by Tayfun Ateş on 1.01.2020.
//

#ifndef ConnectedCarsSimulation_h
#define ConnectedCarsSimulation_h

#include "SimulationColor.h"
#include "ConnectedCarsSettings.h"
#include "SimulationBase.h"
#include "Box2D/Extension/b2VisBody.hpp"
#include "Box2D/Extension/b2VisPolygonShape.hpp"

namespace svqa {
    class ConnectedCarsSimulation : public SimulationBase
    {
    public:
        typedef std::shared_ptr<ConnectedCarsSimulation> Ptr;
        
        struct CarInfo
        {
            BODY* car;
        };
        
        ConnectedCarsSimulation(ConnectedCarsSettings::Ptr _settings_) : SimulationBase(_settings_)
        {
            m_bSceneWithCarsCreated = false;
            m_vSpeedBoundaries = b2Vec2(80.0f, 120.0f);
            m_vXPosBoundaries = b2Vec2(-25.0f, 25.0f);
            
            m_nNumberOfCars = _settings_->numberOfCars;
            
            SET_FILE_OUTPUT_TRUE(m_pSettings->outputFilePath)
        }
        
        virtual CarInfo createCar(const float& speed, const float& xPos)
        {
            SimulationObject carBody = SimulationObject(SimulationObject::CAR_BODY);
            b2PolygonShape carBodyShape = *(std::static_pointer_cast<b2PolygonShape>(carBody.getShape()));
            
            SimulationMaterial mat = SimulationMaterial(SimulationMaterial::METAL);
            int colorIndex = randWithBound(m_nDistinctColorUsed);
            SimulationColor col = SimulationColor((SimulationColor::TYPE) colorIndex);

            b2BodyDef bd;
            bd.type = b2_dynamicBody;
            bd.position.Set(xPos, 1.5f);
            BODY* car = (BODY*) m_world->CreateBody(&bd);
            car->CreateFixture(&carBodyShape, 1.0f);
            car->setTexture(mat.getTexture());
            car->setColor(col.GetColor());
            
    
            SimulationObject wheelBody = SimulationObject(SimulationObject::CAR_WHEEL);
            b2CircleShape wheelBodyShape = *(std::static_pointer_cast<b2CircleShape>(wheelBody.getShape()));
            
            b2FixtureDef fd;
            fd.shape = &wheelBodyShape;
            fd.density = 1.0f;
            fd.friction = 0.9f;

            bd.position.Set(xPos-3.0f, 0.35f);
            BODY* wheel1 = (BODY*) m_world->CreateBody(&bd);
            wheel1->CreateFixture(&fd);
            wheel1->setTexture(mat.getTexture());
            wheel1->setColor(col.GetColor());

            bd.position.Set(xPos+3.0f, 0.4f);
            BODY* wheel2 = (BODY*) m_world->CreateBody(&bd);
            wheel2->CreateFixture(&fd);
            wheel2->setTexture(mat.getTexture());
            wheel2->setColor(col.GetColor());

            b2WheelJointDef jd;
            b2Vec2 axis(0.0f, 1.0f);
            
            float hertz  = 4.0f;
            float zeta = 0.7f;

            jd.Initialize(car, wheel1, wheel1->GetPosition(), axis);
            jd.motorSpeed = speed;
            jd.maxMotorTorque = 200.0f;
            jd.enableMotor = true;
            jd.frequencyHz = hertz;
            jd.dampingRatio = zeta;
            b2WheelJoint* spring1 = (b2WheelJoint*)m_world->CreateJoint(&jd);

            jd.Initialize(car, wheel2, wheel2->GetPosition(), axis);
            jd.motorSpeed = speed;
            jd.maxMotorTorque = 100.0f;
            jd.enableMotor = false;
            jd.frequencyHz = hertz;
            jd.dampingRatio = zeta;
            b2WheelJoint* spring2 = (b2WheelJoint*)m_world->CreateJoint(&jd);
            
            CarInfo res;
            res.car = car;
            return res;
        }
        
        virtual std::vector<CarInfo> createCars(const int& numberOfCars)
        {
            std::vector<CarInfo> res;
            while(1) {
                const bool& reverseDirection = randWithBound(2)==1;
                float speed = RandomFloat(m_vSpeedBoundaries.x, m_vSpeedBoundaries.y);
                if(reverseDirection) {
                    speed *= -1;
                }
                const float& xPos = RandomFloat(m_vXPosBoundaries.x, m_vXPosBoundaries.y);
                bool safe = true;
                for(size_t c=0; c<res.size();c++) {
                    CarInfo currentCarInfo = res[c];
                    if(fabs(xPos - currentCarInfo.car->GetPosition().x)<10.0f) {
                        safe = false;
                        break;
                    }
                }
                
                if(safe) {
                    CarInfo newCarInfo = createCar(speed, xPos);
                    res.push_back(newCarInfo);
                    
                }
                
                if(res.size() >= numberOfCars) {
                    break;
                }
            }
            return res;
        }
        
        virtual void createCarRelations(const std::vector<CarInfo>& cars)
        {
            for(int i=0; i < cars.size()-1; i++) {
                
                int createRelation = randWithBound(2);
                if(createRelation) {
                    const float& length = fabs(cars[i].car->GetPosition().x - cars[i+1].car->GetPosition().x);
                    
                    b2RopeJointDef jd;
                    jd.maxLength = length;
                    jd.collideConnected = true;
                    b2Vec2 p1, p2, d;
                    
                    jd.bodyA = cars[i].car;
                    jd.bodyB = cars[i+1].car;
                    jd.localAnchorA.Set(0.0f, 0.0f);
                    jd.localAnchorB.Set(0.0f, 0.0f);;
                    p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
                    p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
                    d = p2 - p1;
                    b2Joint* joint = m_world->CreateJoint(&jd);
                }
            }
        }
        
        virtual void createInitialScene(const int& numberOfCars)
        {
            auto cars = createCars(numberOfCars);
            
            std::sort(cars.begin(), cars.end(), [] (CarInfo const& a, CarInfo const& b) { return a.car->GetPosition().x < b.car->GetPosition().x; });
            
            createCarRelations(cars);
        }

        virtual void Step(SettingsBase* settings) override
        {
            const bool terminateSimulation = false;
            
            if(!m_bSceneWithCarsCreated) {
                createInitialScene(m_nNumberOfCars);
                m_bSceneWithCarsCreated=true;
            }

            if (terminateSimulation)
            {
                settings->terminate = true;
            }

            SimulationBase::Step(settings);
        }
        
        virtual SimulationID getIdentifier() override
        {
            return SimulationID::ID_ConnectedCars;
        }
        
    private:
    
        bool m_bSceneWithCarsCreated;
        b2Vec2 m_vSpeedBoundaries;
        b2Vec2 m_vXPosBoundaries;
        
        int m_nNumberOfCars;
    };
}


#endif /* ConnectedCarsSimulation_h */
