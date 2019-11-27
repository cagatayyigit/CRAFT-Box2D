//
//  FixedPulleySettings.h
//  Testbed
//
//  Created by Tayfun Ateş on 27.11.2019.
//

#ifndef FixedPulleySettings_h
#define FixedPulleySettings_h

#include "Settings.h"

namespace svqa
{
    struct FixedPulleySettings : Settings
    {
        typedef std::shared_ptr<FixedPulleySettings> Ptr;
        
        FixedPulleySettings() {}
        
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

#endif /* FixedPulleySettings_h */
