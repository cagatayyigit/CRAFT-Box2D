#pragma once

#include "Scene15Settings.h"
#include "SimulationBase.h"
#include "Box2D/Extension/b2VisBody.hpp"
#include "Box2D/Extension/b2VisPolygonShape.hpp"
#include <math.h> 

namespace svqa {
    class Scene15Simulation : public SimulationBase
    {
    public:
        typedef std::shared_ptr<Scene15Simulation> Ptr;
        Scene15Simulation(Scene15Settings::Ptr settings) : SimulationBase(settings)
        {

        }
        
        virtual SimulationID getIdentifier() override
        {
            return SimulationID::ID_Scene15;
        }
        
        void InitializeScene() override {


            
        }
            


    private:

    };
}
