//
//  CausalEventType.h
//  Testbed
//
//  Created by Tayfun Ateş on 28.01.2020.
//

#ifndef CausalEventType_h
#define CausalEventType_h

#include <string>

enum CausalEventType {
    Start_Event = 0,
    End_Event = 1,
    Collision_Event = 2,
    StartTouching_Event = 3,
    EndTouching_Event = 4
};

static std::string getTypeString(CausalEventType type) {
    switch (type) {
        case Start_Event:
            return "Start";
        case End_Event:
            return "End";
        case Collision_Event:
            return "Collision";
        case StartTouching_Event:
            return "StartTouching";
        case EndTouching_Event:
            return "EndTouching";
    }
    return "";
}

#endif /* CausalEventType_h */
