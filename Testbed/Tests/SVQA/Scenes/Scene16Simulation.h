#pragma once

#include "Scene16Settings.h"
#include "SimulationBase.h"
#include "Box2D/Extension/b2VisBody.hpp"
#include "Box2D/Extension/b2VisPolygonShape.hpp"
#include <math.h> 

namespace svqa {
    class Scene16Simulation : public SimulationBase
    {
    public:
        typedef std::shared_ptr<Scene16Simulation> Ptr;
        Scene16Simulation(Scene16Settings::Ptr settings) : SimulationBase(settings)
        {

        }
        
        virtual SimulationID getIdentifier() override
        {
            return SimulationID::ID_Scene16;
        }
        
        void InitializeScene() override {


           
        }
            


    private:

    };
}
