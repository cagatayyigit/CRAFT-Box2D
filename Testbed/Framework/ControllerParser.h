//
//  ControllerParser.h
//  Testbed
//
//  Created by Tayfun Ateş on 17.11.2019.
//

#ifndef ControllerParser_h
#define ControllerParser_h

#include "RemoveObjectSimulationSettings.h"
#include "RemoveObjectSimulation.h"
#include "JSONHelper.h"

namespace ips {
    RemoveObjectSimulation::Ptr parse(const std::string& inputFile)
    {
        IPSSettings set;
        json j;
        bool fileLoadRes = JSONHelper::loadJSON(j, inputFile);
        if(fileLoadRes) {
            set.from_json(j);
            if(set.simulationName == RemoveObjectSimulation::name()) {
                RemoveObjectSimulationSettings::Ptr setPtr = std::make_shared<RemoveObjectSimulationSettings>();
                setPtr->from_json(j);
                return std::make_shared<RemoveObjectSimulation>(setPtr);
            }
        }
        return nullptr;
        
    }
}

#endif /* ControllerParser_h */
