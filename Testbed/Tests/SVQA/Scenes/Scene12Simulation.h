#pragma once

#include "Scene12Settings.h"
#include "SimulationBase.h"
#include "Box2D/Extension/b2VisBody.hpp"
#include "Box2D/Extension/b2VisPolygonShape.hpp"
#include <math.h> 

namespace svqa {
    class Scene12Simulation : public SimulationBase
    {
    public:
        typedef std::shared_ptr<Scene12Simulation> Ptr;
        Scene12Simulation(Scene12Settings::Ptr settings) : SimulationBase(settings)
        {

        }
        
        virtual SimulationID getIdentifier() override
        {
            return SimulationID::ID_Scene12;
        }
        
        void InitializeScene() override {



            // Basket
            float basket_pos_x = getExtremeCases(m_sStaticObjectOrientationType, -1.0f, 1.0f);
            AddTargetBasket(b2Vec2(0.0f, -1.2f), 0.0f);
            
            // Right platform
            float right_platform_pos_x = 12.0f;
            AddStaticObject(b2Vec2(right_platform_pos_x, 8.0f), M_PI / 5.0f, SimulationObject::STATIC_PLATFORM);

            // Left platform
            float left_platform_pos_x = -12.0f;
            AddStaticObject(b2Vec2(left_platform_pos_x, 8.0f), -M_PI / 5.0f, SimulationObject::STATIC_PLATFORM);

            // Static ball
            float static_ball_pos_y = 13.0f;
            AddStaticObject(b2Vec2(0.0f, static_ball_pos_y), 0, SimulationObject::STATIC_BALL);



            if (m_bIncludeDynamicObjects) {

                
                AddRandomDynamicObject(
                    b2Vec2(right_platform_pos_x, 36.5f),
                    b2Vec2(0.0f, 0.0f),
                    0b000,
                    SimulationObject::CIRCLE
                );

                AddRandomDynamicObject(
                    b2Vec2(left_platform_pos_x, 36.5f),
                    b2Vec2(0.0f, 0.0f),
                    0b000,
                    SimulationObject::CIRCLE
                );

                AddRandomDynamicObject(
                    b2Vec2(0.1f, 36.5f),
                    b2Vec2(0.0f, 0.0f),
                    0b000,
                    SimulationObject::CIRCLE
                );

            }
        }
            


    private:

    };
}
