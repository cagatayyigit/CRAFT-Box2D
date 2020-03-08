//
//  SceneState.h
//  Testbed
//
//  Created by Tayfun Ateş on 20.10.2019.
//

#ifndef SceneState_h
#define SceneState_h

#include <iostream>
#include "SimulationDefines.h"
#include <nlohmann/json.hpp>
#include "ObjectState.h"
#include "JSONHelper.h"
#include "Box2D/Extension/b2VisWorld.hpp"

using json = nlohmann::json;

struct SceneState {

    void add(const ObjectState::Ptr& objState)
    {
        objects.push_back(objState);
    }
    
    void clear()
    {
        objects.clear();
    }
    
    bool loadFromJSONFile(std::string fromFile, WORLD* toWorld) {
        if(toWorld) {
            json j;
            bool fileLoadRes = JSONHelper::loadJSON(j, fromFile);
            
            if(fileLoadRes) {
                clear();
                
                for (auto& [key, value] : j.items()) {
                    ObjectState::Ptr oState = std::make_shared<ObjectState>();
                    oState->from_json(value, toWorld);
                    add(oState);
                }
                
                return true;
            }
        }
        return false;
    }
    
    json toJSON() const
    {
        json jScene;
        for (int i=objects.size()-1 ; i>=0; i--) {
            const auto& object = objects[i];
            json jObject;
            object->to_json(jObject);
            jScene.push_back(jObject);
        }
        return jScene;
    }
    
    bool saveToJSONFile(WORLD* fromWorld, std::string toFile) const {
        if(fromWorld) {
            return JSONHelper::saveJSON(toJSON(), toFile);
        }
        return false;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const SceneState& state)
    {
        os << state.toJSON();
        return os;
    }
    
private:
    std::vector<ObjectState::Ptr> objects;
};

#endif /* SceneState_h */
