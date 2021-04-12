#pragma once

#include "Scene11Settings.h"
#include "SimulationBase.h"
#include "Box2D/Extension/b2VisBody.hpp"
#include "Box2D/Extension/b2VisPolygonShape.hpp"
#include <math.h> 

namespace svqa {
    class Scene11Simulation : public SimulationBase
    {
    public:
        typedef std::shared_ptr<Scene11Simulation> Ptr;
        Scene11Simulation(Scene11Settings::Ptr settings) : SimulationBase(settings)
        {

        }
        
        virtual SimulationID getIdentifier() override
        {
            return SimulationID::ID_Scene11;
        }
        
        void InitializeScene() override {
            
            
            // Basket
            AddTargetBasket(b2Vec2(RandomFloatFromHardware(-3.0, 3.0), -1.2f), 0.0f);
            
            
            // Bottom Left  Floor
            AddStaticObject(b2Vec2(-12.0f, 6.0f), 0, SimulationObject::STATIC_PLATFORM);
            
            // Bottom Right Floor
            float x = RandomFloatFromHardware(12, 18);
            AddStaticObject(b2Vec2(x, 6.0f), 0, SimulationObject::STATIC_PLATFORM);
            
            
            // Bottom Left  Vertical Floor
            AddStaticObject(b2Vec2(-28.0f, 12.0f), 4 * M_PI / 5, SimulationObject::STATIC_PLATFORM);
            AddRandomDynamicObject(
                b2Vec2(-23.0f,14.0f),
                b2Vec2(0.0f, 0.0f)
            );
            
            
            // Middle Left  Floor
            AddStaticObject(b2Vec2(-5.0f, 18.0f), 50 * M_PI / RandomFloatFromHardware(51.2, 57.0), SimulationObject::STATIC_PLATFORM);
            
            AddRandomDynamicObject(
                b2Vec2(-5.0f,  20.0f),
                b2Vec2(0.0f, 0.0f)
            );
            
            
            // Middle Right Floor
            AddStaticObject(b2Vec2(16.0f, RandomFloatFromHardware(22, 26)), - 50 * M_PI / RandomFloatFromHardware(51.2, 57.0), SimulationObject::STATIC_PLATFORM);
            AddRandomDynamicObject(
                b2Vec2(16.0f,  29.0f),
                b2Vec2(0.0f, 0.0f)
            );
            
            float height = RandomFloatFromHardware(26, 30);
            
            AddRandomDynamicObject(
                b2Vec2(-2.0f, height + 9.0f),
                b2Vec2(-8.0f, -8.0f)
            );
            
            AddRandomDynamicObject(
                b2Vec2(-7.0f, height + 2.0f),
                b2Vec2(0.0f, 0.0f)
            );
            AddStaticObject(b2Vec2(-10.0f, height), 0, SimulationObject::STATIC_PLATFORM);
            
            
            // Stationary Bottom-Left
            AddRandomDynamicObject(
                b2Vec2(-8.0f, 9.0f),
                b2Vec2(0.0f, 0.0f)
            );
            
        }
        
    private:

    };
}
