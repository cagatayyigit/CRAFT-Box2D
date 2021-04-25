#pragma once

#include "Scene14Settings.h"
#include "SimulationBase.h"
#include "Box2D/Extension/b2VisBody.hpp"
#include "Box2D/Extension/b2VisPolygonShape.hpp"
#include <math.h> 

namespace svqa {
    class Scene14Simulation : public SimulationBase
    {
    public:
        typedef std::shared_ptr<Scene14Simulation> Ptr;
        Scene14Simulation(Scene14Settings::Ptr settings) : SimulationBase(settings)
        {

        }
        
        virtual SimulationID getIdentifier() override
        {
            return SimulationID::ID_Scene14;
        }
        
        void InitializeScene() override {


        }
            


    private:

    };
}
