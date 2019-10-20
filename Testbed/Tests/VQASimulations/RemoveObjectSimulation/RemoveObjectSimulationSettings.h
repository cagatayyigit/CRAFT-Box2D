//
//  RemoveObjectSimulationSettings.h
//  Testbed
//
//  Created by Tayfun Ateş on 20.10.2019.
//

#ifndef RemoveObjectSimulationSettings_h
#define RemoveObjectSimulationSettings_h

#include "SimulationSettings.h"

struct RemoveObjectSimulationSettings : SimulationSettings
{
    RemoveObjectSimulationSettings(const int& simId,
                                   const int& width,
                                   const int& height,
                                   const std::string& scenePath,
                                   const int& noObjects) : numberOfObjects(noObjects), SimulationSettings(simId, width, height, scenePath) {}
    
    int numberOfObjects;
    
    void to_json(json& j) {
        j.emplace("numberOfObjects", this->numberOfObjects);
        SimulationSettings::to_json(j);
    }

    void from_json(const json& j) {
        SimulationSettings::from_json(j);
        j.at("numberOfObjects").get_to(this->numberOfObjects);
    }
};


#endif /* RemoveObjectSimulationSettings_h */
