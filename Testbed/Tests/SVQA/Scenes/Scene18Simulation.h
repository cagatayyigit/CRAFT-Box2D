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


   
        }
            


    private:

    };
}
