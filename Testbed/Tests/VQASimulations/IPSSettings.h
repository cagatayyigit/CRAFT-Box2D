//
//  SimulationSettings.h
//  Testbed
//
//  Created by Tayfun Ateş on 20.10.2019.
//

#ifndef IPSSettings_h
#define IPSSettings_h

#include "Simulation.h"
#include <string>
#include <nlohmann/json.hpp>
#include <iostream>

using json = nlohmann::json;

struct IPSSettings : public Settings
{
    typedef std::shared_ptr<IPSSettings> Ptr;
    
    IPSSettings() {}
    virtual ~IPSSettings() {};
    
    std::string simulationName;
    int simulationID;
    bool offline;
    std::string inputScenePath;
    std::string outputFilePath;
    
    void to_json(json& j) {
        j.emplace("simulationName", this->simulationName);
        j.emplace("simulationID", this->simulationID);
        j.emplace("offline", this->offline);
        j.emplace("width", this->bufferWidth);
        j.emplace("height", this->bufferHeight);
        j.emplace("inputScenePath", this->inputScenePath);
        j.emplace("outputFilePath", this->outputFilePath);
    }

    void from_json(const json& j) {
        j.at("simulationName").get_to(this->simulationName);
        j.at("simulationID").get_to(this->simulationID);
        j.at("offline").get_to(this->offline);
        j.at("width").get_to(this->bufferWidth);
        j.at("height").get_to(this->bufferHeight);
        j.at("inputScenePath").get_to(this->inputScenePath);
        j.at("outputFilePath").get_to(this->outputFilePath);
    }
};



#endif /* IPSSettings_h */
