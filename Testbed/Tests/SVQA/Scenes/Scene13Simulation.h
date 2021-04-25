#pragma once

#include "Scene13Settings.h"
#include "SimulationBase.h"
#include "Box2D/Extension/b2VisBody.hpp"
#include "Box2D/Extension/b2VisPolygonShape.hpp"
#include <math.h> 

namespace svqa {
    class Scene13Simulation : public SimulationBase
    {
    public:
        typedef std::shared_ptr<Scene13Simulation> Ptr;
        Scene13Simulation(Scene13Settings::Ptr settings) : SimulationBase(settings)
        {

        }
        
        virtual SimulationID getIdentifier() override
        {
            return SimulationID::ID_Scene13;
        }
        
        void InitializeScene() override {


            // Basket   
            float basket_pos_x = -18.0f;
            AddTargetBasket(b2Vec2(basket_pos_x, -1.2f), 0.0f);


            // Static ball right
            float static_ball_1_pos_x = -6.0f;
            float static_ball_1_pos_y = 10.0f;
            AddStaticObject(b2Vec2(static_ball_1_pos_x, static_ball_1_pos_y), 0, SimulationObject::STATIC_BALL);

            // Static ball middle
            float static_ball_2_pos_x = -12.0f;
            float static_ball_2_pos_y = 20.0f;
            AddStaticObject(b2Vec2(static_ball_2_pos_x, static_ball_2_pos_y), 0, SimulationObject::STATIC_BALL);

            // Static ball left
            float static_ball_3_pos_x = -18.0f;
            float static_ball_3_pos_y = 30.0f;
            AddStaticObject(b2Vec2(static_ball_3_pos_x, static_ball_3_pos_y), 0, SimulationObject::STATIC_BALL);

            // Platforms that are composed of two or more parts can be implemented like this.
            // Right upper inclined platform
            float angle = M_PI / 5.0f;
            // Right upper inclined platform part 1
            float right_upper_platform_pos_x = 18.0f;
            float right_upper_platform_pos_y = 28.0f;
            AddStaticObject(b2Vec2(right_upper_platform_pos_x, right_upper_platform_pos_y), angle, SimulationObject::STATIC_PLATFORM);
            // Right upper inclined platform part 2
            float right_upper_platform_2_pos_x = right_upper_platform_pos_x - cos(angle) * 8.0 * 2;
            float right_upper_platform_2_pos_y = right_upper_platform_pos_y - sin(angle) * 8.0 * 2;
            AddStaticObject(b2Vec2(right_upper_platform_2_pos_x, right_upper_platform_2_pos_y), angle, SimulationObject::STATIC_PLATFORM);

            // Platforms that are composed of two or more parts can be implemented like this.
            // Right lower inclined platform
            angle = M_PI / 5.0f;
            // Right lower inclined platform part 1
            float right_lower_platform_pos_x = 18.0f;
            float right_lower_platform_pos_y = 20.0f;
            AddStaticObject(b2Vec2(right_lower_platform_pos_x, right_lower_platform_pos_y), angle, SimulationObject::STATIC_PLATFORM);
            // Right lower inclined platform part 2
            float right_lower_platform_2_pos_x = right_lower_platform_pos_x - cos(angle) * 8.0 * 2;
            float right_lower_platform_2_pos_y = right_lower_platform_pos_y - sin(angle) * 8.0 * 2;
            AddStaticObject(b2Vec2(right_lower_platform_2_pos_x, right_lower_platform_2_pos_y), angle, SimulationObject::STATIC_PLATFORM);

            // Upper platform
            float upper_platform_pos_x = -12.0f;
            float upper_platform_pos_y = 36.0f;
            AddStaticObject(b2Vec2(upper_platform_pos_x, upper_platform_pos_y), 0, SimulationObject::STATIC_PLATFORM);
            
            if (m_bIncludeDynamicObjects) {
                AddRandomDynamicObject(
                    b2Vec2(b2Vec2(upper_platform_pos_x, upper_platform_pos_y + 1)),
                    b2Vec2(0.0f, 0.0f)
                );
                AddRandomDynamicObject(
                    b2Vec2(b2Vec2(right_lower_platform_pos_x, right_lower_platform_pos_y + 1)),
                    b2Vec2(0.0f, 0.0f)
                );
                AddRandomDynamicObject(
                    b2Vec2(b2Vec2(right_upper_platform_pos_x, right_upper_platform_pos_y + 1)),
                    b2Vec2(0.0f, 0.0f)
                );
            }
        }
            


    private:

    };
}
