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




        }
            


    private:

    };
}
