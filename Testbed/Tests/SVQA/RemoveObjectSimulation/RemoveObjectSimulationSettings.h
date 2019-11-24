//
//  RemoveObjectSimulationSettings.h
//  Testbed
//
//  Created by Tayfun Ateş on 20.10.2019.
//

#ifndef RemoveObjectSimulationSettings_h
#define RemoveObjectSimulationSettings_h

#include "Settings.h"

namespace svqa
{
    struct RemoveObjectSimulationSettings : Settings
    {
        typedef std::shared_ptr<RemoveObjectSimulationSettings> Ptr;
        
        RemoveObjectSimulationSettings() {}
        
        int numberOfObjects;
        
        void to_json(json& j) {
            j.emplace("numberOfObjects", this->numberOfObjects);
            Settings::to_json(j);
        }

        void from_json(const json& j) {
            Settings::from_json(j);
            j.at("numberOfObjects").get_to(this->numberOfObjects);
        }
    };
}

#endif /* RemoveObjectSimulationSettings_h */
