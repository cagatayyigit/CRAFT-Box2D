//
//  SimulationObject.h
//  Testbed
//
//  Created by Tayfun Ateş on 9.10.2019.
//

#ifndef SimulationObject_h
#define SimulationObject_h

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

#endif /* SimulationObject_h */
