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
            return "StartEvent";
        case End_Event:
            return "EndEvent";
        case Collision_Event:
            return "CollisionEvent";
        case StartTouching_Event:
            return "StartTouchingEvent";
        case EndTouching_Event:
            return "EndTouchingEvent";
    }
    return "";
}

#endif /* CausalEventType_h */
