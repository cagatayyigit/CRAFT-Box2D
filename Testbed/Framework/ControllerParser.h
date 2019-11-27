//
//  ControllerParser.h
//  Testbed
//
//  Created by Tayfun Ateş on 17.11.2019.
//

#ifndef ControllerParser_h
#define ControllerParser_h

#include "RemoveObjectSimulation.h"
#include "ObstructedPathSimulation.h"
#include "PendulumObstaclesSimulation.h"
#include "FixedPulleySimulation.h"
#include "JSONHelper.h"

namespace svqa {
    SimulationBase::Ptr parse(const std::string& inputFile)
    {
        Settings set;
        json j;
        bool fileLoadRes = JSONHelper::loadJSON(j, inputFile);
        if(fileLoadRes) {
            set.from_json(j);
            if(set.simulationID == SimulationID::ID_RemoveObject) {
                RemoveObjectSimulationSettings::Ptr setPtr = std::make_shared<RemoveObjectSimulationSettings>();
                setPtr->from_json(j);
                return std::make_shared<RemoveObjectSimulation>(setPtr);
            } else if(set.simulationID == SimulationID::ID_ObstructedPath) {
                ObstructedPathSettings::Ptr setPtr = std::make_shared<ObstructedPathSettings>();
                setPtr->from_json(j);
                return std::make_shared<ObstructedPathSimulation>(setPtr);
            } else if(set.simulationID == SimulationID::ID_PendulumObstacles) {
                PendulumObstaclesSettings::Ptr setPtr = std::make_shared<PendulumObstaclesSettings>();
                setPtr->from_json(j);
                return std::make_shared<PendulumObstaclesSimulation>(setPtr);
            } else if(set.simulationID == SimulationID::ID_FixedPulley) {
                FixedPulleySettings::Ptr setPtr = std::make_shared<FixedPulleySettings>();
                setPtr->from_json(j);
                return std::make_shared<FixedPulleySimulation>(setPtr);
            }
        }
        return nullptr;
        
    }
}

#endif /* ControllerParser_h */
