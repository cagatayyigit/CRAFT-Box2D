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
#include "Scene2Simulation.h"
#include "Scene3Simulation.h"
#include "Scene4Simulation.h"
#include "Scene5Simulation.h"
#include "Scene6Simulation.h"

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
			else if (set.simulationID == SimulationID::ID_Scene2) {
				Scene2Settings::Ptr setPtr = std::make_shared<Scene2Settings>();
				setPtr->from_json(j);
				return std::make_shared<Scene2Simulation>(setPtr);
			}
			else if (set.simulationID == SimulationID::ID_Scene3) {
				Scene3Settings::Ptr setPtr = std::make_shared<Scene3Settings>();
				setPtr->from_json(j);
				return std::make_shared<Scene3Simulation>(setPtr);
			}
			else if (set.simulationID == SimulationID::ID_Scene4) {
				Scene4Settings::Ptr setPtr = std::make_shared<Scene4Settings>();
				setPtr->from_json(j);
				return std::make_shared<Scene4Simulation>(setPtr);
			}
			else if (set.simulationID == SimulationID::ID_Scene5) {
				Scene5Settings::Ptr setPtr = std::make_shared<Scene5Settings>();
				setPtr->from_json(j);
				return std::make_shared<Scene5Simulation>(setPtr);
			}
			else if (set.simulationID == SimulationID::ID_Scene6) {
				Scene6Settings::Ptr setPtr = std::make_shared<Scene6Settings>();
				setPtr->from_json(j);
				return std::make_shared<Scene6Simulation>(setPtr);
			}
        }
        return nullptr;
        
    }
}

#endif /* ControllerParser_h */
