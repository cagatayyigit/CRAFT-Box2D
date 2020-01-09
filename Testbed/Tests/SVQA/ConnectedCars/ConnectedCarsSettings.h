//
//  ConnectedCarsSettings.h
//  Testbed
//
//  Created by Tayfun Ateş on 1.01.2020.
//

#ifndef ConnectedCarsSettings_h
#define ConnectedCarsSettings_h

#include "Settings.h"

namespace svqa
{
    struct ConnectedCarsSettings : Settings
    {
        typedef std::shared_ptr<ConnectedCarsSettings> Ptr;
        
        ConnectedCarsSettings() {}
        
        int numberOfCars;
        
        void to_json(json& j) {
            j.emplace("numberOfCars", this->numberOfCars);
            Settings::to_json(j);
        }

        void from_json(const json& j) {
            Settings::from_json(j);
            j.at("numberOfCars").get_to(this->numberOfCars);
        }
    };
}


#endif /* ConnectedCarsSettings_h */
