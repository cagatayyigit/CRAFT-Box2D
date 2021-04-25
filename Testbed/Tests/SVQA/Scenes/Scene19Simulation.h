#pragma once

#include "Scene19Settings.h"
#include "SimulationBase.h"
#include "Box2D/Extension/b2VisBody.hpp"
#include "Box2D/Extension/b2VisPolygonShape.hpp"
#include <math.h> 

namespace svqa {
    class Scene19Simulation : public SimulationBase
    {
    public:
        typedef std::shared_ptr<Scene19Simulation> Ptr;
        Scene19Simulation(Scene19Settings::Ptr settings) : SimulationBase(settings)
        {

        }
        
        virtual SimulationID getIdentifier() override
        {
            return SimulationID::ID_Scene19;
        }
        
        void InitializeScene() override {


        }
            


    private:

    };
}
