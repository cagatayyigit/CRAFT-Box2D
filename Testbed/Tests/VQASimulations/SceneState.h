//
//  SceneState.h
//  Testbed
//
//  Created by Tayfun Ateş on 20.10.2019.
//

#ifndef SceneState_h
#define SceneState_h

#include <iostream>
#include <nlohmann/json.hpp>
#include "ObjectState.h"

using json = nlohmann::json;

struct SceneState {

    void add(const ObjectState& objState)
    {
        json j;
        objState.to_json(j);
        jsonHandler.push_back(j);
    }
    
    void clear()
    {
        jsonHandler.clear();
    }
    
    friend std::ostream& operator<<(std::ostream& os, const SceneState& state)
    {
        os << state.jsonHandler;
        return os;
    }
    
    json jsonHandler;
};

#endif /* SceneState_h */
