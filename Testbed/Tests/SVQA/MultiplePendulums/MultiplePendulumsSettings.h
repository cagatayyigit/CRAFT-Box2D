//
//  MultiplePendulumsSettings.h
//  Testbed
//
//  Created by Tayfun Ateş on 11.01.2020.
//

#ifndef MultiplePendulumsSettings_h
#define MultiplePendulumsSettings_h

#include "Settings.h"

namespace svqa
{
    struct MultiplePendulumsSettings : Settings
    {
        typedef std::shared_ptr<MultiplePendulumsSettings> Ptr;
        
        MultiplePendulumsSettings() {}
        
        int numberOfObjects;
        int numberOfPendulums;
        
        void to_json(json& j) {
            j.emplace("numberOfObjects", this->numberOfObjects);
            j.emplace("numberOfPendulums", this->numberOfPendulums);
            Settings::to_json(j);
        }

        void from_json(const json& j) {
            Settings::from_json(j);
            j.at("numberOfObjects").get_to(this->numberOfObjects);
            j.at("numberOfPendulums").get_to(this->numberOfPendulums);
        }
    };
}

#endif /* MultiplePendulumsSettings_h */
