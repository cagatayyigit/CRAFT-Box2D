//
//  PendulumObstaclesSettings.h
//  Testbed
//
//  Created by Tayfun Ateş on 25.11.2019.
//

#ifndef PendulumObstaclesSettings_h
#define PendulumObstaclesSettings_h

#include "Settings.h"

namespace svqa
{
    struct PendulumObstaclesSettings : Settings
    {
        typedef std::shared_ptr<PendulumObstaclesSettings> Ptr;
        
        PendulumObstaclesSettings() {}
        
        int numberOfObjects;
        int numberOfObstacles;
        
        void to_json(json& j) {
            j.emplace("numberOfObjects", this->numberOfObjects);
            j.emplace("numberOfObstacles", this->numberOfObstacles);
            Settings::to_json(j);
        }

        void from_json(const json& j) {
            Settings::from_json(j);
            j.at("numberOfObjects").get_to(this->numberOfObjects);
            j.at("numberOfObstacles").get_to(this->numberOfObstacles);
        }
    };
}

#endif /* PendulumObstaclesSettings_h */
