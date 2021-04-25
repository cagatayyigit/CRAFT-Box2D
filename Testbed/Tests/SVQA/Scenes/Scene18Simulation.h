#pragma once

#include "Scene18Settings.h"
#include "SimulationBase.h"
#include "Box2D/Extension/b2VisBody.hpp"
#include "Box2D/Extension/b2VisPolygonShape.hpp"
#include <math.h> 

namespace svqa {
    class Scene18Simulation : public SimulationBase
    {
    public:
        typedef std::shared_ptr<Scene18Simulation> Ptr;
        Scene18Simulation(Scene18Settings::Ptr settings) : SimulationBase(settings)
        {

        }
        
        virtual SimulationID getIdentifier() override
        {
            return SimulationID::ID_Scene18;
        }
        
        void InitializeScene() override {


            /*
            * NOT IMPLEMENTED
            */


            // Basket
            float basket_pos_x = getExtremeCases(m_sStaticObjectOrientationType, 18.0f, 21.0f);
            AddTargetBasket(b2Vec2(basket_pos_x, -1.2f), 0.0f);
            
            // Right platform
            float right_platform_pos_x = 12.0f;
            AddStaticObject(b2Vec2(right_platform_pos_x, 5.0f), 0, SimulationObject::STATIC_PLATFORM);

            // Left platform
            float left_platform_pos_x = -12.0f;
            AddStaticObject(b2Vec2(left_platform_pos_x, 5.0f), 0, SimulationObject::STATIC_PLATFORM);

            // Static ball
            float static_ball_pos_y = 3.5f;
            AddStaticObject(b2Vec2(0.0f, static_ball_pos_y), 0, SimulationObject::STATIC_BALL);


            // Right inclined-platform     
            AddStaticObject(b2Vec2(right_platform_pos_x, 32.0f), M_PI / 5.0f , SimulationObject::STATIC_PLATFORM);

            // Left inclined-platform
            AddStaticObject(b2Vec2(left_platform_pos_x + 4.0f, 18.0f), M_PI / 5.0f , SimulationObject::STATIC_PLATFORM);



            if (m_bIncludeDynamicObjects) {

                // Circle on the Right platform
                AddRandomDynamicObject(
                    b2Vec2(right_platform_pos_x, 6.5f),
                    b2Vec2(-15.0f, 0.0f),
                    0b000,
                    SimulationObject::CIRCLE
                );

                // Circle on the Left platform
                AddRandomDynamicObject(
                    b2Vec2(left_platform_pos_x, 6.5f),
                    b2Vec2(15.0f, 0.0f),
                    0b000,
                    SimulationObject::CIRCLE
                );

                // Circle on the Right inclined-platform
                AddRandomDynamicObject(
                    b2Vec2(right_platform_pos_x + 2.0f, 37.5f),
                    b2Vec2(0.0f, 0.0f),
                    0b000,
                    SimulationObject::CIRCLE
                );
            }
        }
            


    private:

    };
}
