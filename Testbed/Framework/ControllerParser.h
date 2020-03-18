//
//  ControllerParser.h
//  Testbed
//
//  Created by Tayfun Ateş on 17.11.2019.
//

#ifndef ControllerParser_h
#define ControllerParser_h

#include "ObstructionDemoSimulation.h"
#include "Scene1Simulation.h"

#include "JSONHelper.h"

namespace svqa {
    SimulationBase::Ptr parse(const std::string& inputFile)
    {
        Settings set;
        json j;
        bool fileLoadRes = JSONHelper::loadJSON(j, inputFile);
        if(fileLoadRes) {
            set.from_json(j);    
			if (set.simulationID == SimulationID::ID_ObstructionDemo) {
				ObstructionDemoSettings::Ptr setPtr = std::make_shared<ObstructionDemoSettings>();
				setPtr->from_json(j);
				return std::make_shared<ObstructionDemoSimulation>(setPtr);
			}
			else if (set.simulationID == SimulationID::ID_Scene1) {
				Scene1Settings::Ptr setPtr = std::make_shared<Scene1Settings>();
				setPtr->from_json(j);
				return std::make_shared<Scene1Simulation>(setPtr);
			}
            
        }
        return nullptr;
        
    }
}

#endif /* ControllerParser_h */
