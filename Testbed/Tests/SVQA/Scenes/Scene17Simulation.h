#pragma once

#include "Scene17Settings.h"
#include "SimulationBase.h"
#include "Box2D/Extension/b2VisBody.hpp"
#include "Box2D/Extension/b2VisPolygonShape.hpp"
#include <math.h> 

namespace svqa {
    class Scene17Simulation : public SimulationBase
    {
    public:
        typedef std::shared_ptr<Scene17Simulation> Ptr;
        Scene17Simulation(Scene17Settings::Ptr settings) : SimulationBase(settings)
        {

        }
        
        virtual SimulationID getIdentifier() override
        {
            return SimulationID::ID_Scene17;
        }
        
        void InitializeScene() override {


        }
            


    private:

    };
}
