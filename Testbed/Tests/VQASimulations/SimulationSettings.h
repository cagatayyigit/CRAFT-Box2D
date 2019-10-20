//
//  SimulationSettings.h
//  Testbed
//
//  Created by Tayfun Ateş on 20.10.2019.
//

#ifndef SimulationSettings_h
#define SimulationSettings_h

#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct SimulationSettings
{
    SimulationSettings(const int& simId, const int& width, const int& height, const std::string& scenePath) : simulationID(simId), camWidth(width), camHeight(height), scenePath(scenePath) {}
    virtual ~SimulationSettings() {};
    
    int simulationID;
    int camWidth;
    int camHeight;
    std::string scenePath;
    
    void to_json(json& j) {
        j.emplace("simulationID", this->simulationID);
        j.emplace("camWidth", this->camWidth);
        j.emplace("camHeight", this->camHeight);
        j.emplace("scenePath", this->scenePath);
    }

    void from_json(const json& j) {
        j.at("simulationID").get_to(this->simulationID);
        j.at("camWidth").get_to(this->camWidth);
        j.at("camHeight").get_to(this->camHeight);
        j.at("scenePath").get_to(this->scenePath);
    }
};



#endif /* SimulationSettings_h */
