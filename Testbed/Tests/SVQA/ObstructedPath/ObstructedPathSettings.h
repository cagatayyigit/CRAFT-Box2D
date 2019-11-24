//
//  ObstructedPathSettings.h
//  Testbed
//
//  Created by Tayfun Ateş on 24.11.2019.
//

#ifndef ObstructedPathSettings_h
#define ObstructedPathSettings_h

#include "Settings.h"

namespace svqa
{
    struct ObstructedPathSettings : Settings
    {
        typedef std::shared_ptr<ObstructedPathSettings> Ptr;
        
        ObstructedPathSettings() {}
        
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

#endif /* ObstructedPathSettings_h */
