//
//  Settings.h
//  Testbed
//
//  Created by Tayfun Ateş on 20.10.2019.
//

#ifndef Settings_h
#define Settings_h

#include "Simulation.h"
#include <string>
#include <nlohmann/json.hpp>
#include <iostream>
#include "SimulationID.h"

using json = nlohmann::json;

namespace svqa
{
    struct Settings : public SettingsBase
    {
        typedef std::shared_ptr<Settings> Ptr;
        
        Settings() {}
        virtual ~Settings() {};
        
        SimulationID simulationID;
        bool offline;
        std::string inputScenePath;
        std::string outputVideoPath;
        std::string outputJSONPath;

        std::string staticObjectPositioningType;
        bool includeDynamicObjectsInTheScene;
        
        void to_json(json& j) {
            j.emplace("simulationID", (int)this->simulationID);
            j.emplace("offline", this->offline);
            j.emplace("width", this->bufferWidth);
            j.emplace("height", this->bufferHeight);
            j.emplace("inputScenePath", this->inputScenePath);
            j.emplace("outputVideoPath", this->outputVideoPath);
            j.emplace("outputJSONPath", this->outputJSONPath);
            j.emplace("stepCount", this->stepCount);
            j.emplace("includeDynamicObjects", this->includeDynamicObjectsInTheScene);
            j.emplace("staticObjectPositioningType",   this->staticObjectPositioningType);
        }

        void from_json(const json& j) {
            j.at("simulationID").get_to(this->simulationID);
            j.at("offline").get_to(this->offline);
            j.at("width").get_to(this->bufferWidth);
            j.at("height").get_to(this->bufferHeight);
            j.at("inputScenePath").get_to(this->inputScenePath);
            j.at("outputVideoPath").get_to(this->outputVideoPath);
            j.at("outputJSONPath").get_to(this->outputJSONPath);
            j.at("stepCount").get_to(this->stepCount);
            auto includeDynamicObjectsInTheScene = j.find("includeDynamicObjects");
            if (includeDynamicObjectsInTheScene != j.end())
            {
                this->includeDynamicObjectsInTheScene = *includeDynamicObjectsInTheScene;
            }
            auto staticObjectPositioningType = j.find("staticObjectPositioningType");
            if (staticObjectPositioningType != j.end())
            {
                std::string value = *staticObjectPositioningType;
                if (value != "min"
                    && value != "mean"
                    && value != "max"
                    && value != "random")
                {
                    throw "Static object positioning type must be one of the following: min, mean, max, random";
                }
                
                this->staticObjectPositioningType = value;
            }
        }
    };
}

#endif /* Settings_h */
