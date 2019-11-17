//
//  RemoveObjectSimulationSettings.h
//  Testbed
//
//  Created by Tayfun Ateş on 20.10.2019.
//

#ifndef RemoveObjectSimulationSettings_h
#define RemoveObjectSimulationSettings_h

#include "IPSSettings.h"

struct RemoveObjectSimulationSettings : IPSSettings
{
    typedef std::shared_ptr<RemoveObjectSimulationSettings> Ptr;
    
    RemoveObjectSimulationSettings() {}
    
    int numberOfObjects;
    
    void to_json(json& j) {
        j.emplace("numberOfObjects", this->numberOfObjects);
        IPSSettings::to_json(j);
    }

    void from_json(const json& j) {
        IPSSettings::from_json(j);
        j.at("numberOfObjects").get_to(this->numberOfObjects);
    }
};


#endif /* RemoveObjectSimulationSettings_h */
