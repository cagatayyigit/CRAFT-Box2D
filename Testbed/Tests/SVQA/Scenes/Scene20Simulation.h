#pragma once

#include "Scene20Settings.h"
#include "SimulationBase.h"
#include "Box2D/Extension/b2VisBody.hpp"
#include "Box2D/Extension/b2VisPolygonShape.hpp"
#include <math.h> 

namespace svqa {
    class Scene20Simulation : public SimulationBase
    {
    public:
        typedef std::shared_ptr<Scene20Simulation> Ptr;
        Scene20Simulation(Scene20Settings::Ptr settings) : SimulationBase(settings)
        {

        }
        
        virtual SimulationID getIdentifier() override
        {
            return SimulationID::ID_Scene20;
        }
        
        void InitializeScene() override {


        }
            


    private:

    };
}
