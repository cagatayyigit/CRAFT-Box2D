//
//  SimulationObject.h
//  Testbed
//
//  Created by Tayfun Ateş on 9.10.2019.
//

#ifndef SimulationObject_h
#define SimulationObject_h

#include <nlohmann/json.hpp>

class SimulationObject
{
public:
    enum TYPE
    {
        SMALL_CUBE = 0,
        BIG_CUBE = 1,
    };

    SimulationObject(TYPE t)
    {
        type = t;
    }

    float GetEdgeLength()
    {
        if(type == SMALL_CUBE)
        {
            return 1.0f;
        }
        return 2.0f;
    }

    TYPE type;
};

NLOHMANN_JSON_SERIALIZE_ENUM( SimulationObject::TYPE, {
    {SimulationObject::SMALL_CUBE, "small_cube"},
    {SimulationObject::BIG_CUBE, "big_cube"}
})

#endif /* SimulationObject_h */
