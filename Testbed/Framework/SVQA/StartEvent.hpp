//
//  StartEvent.hpp
//  Testbed
//
//  Created by Tayfun Ateş on 28.01.2020.
//

#ifndef StartEvent_hpp
#define StartEvent_hpp

#include "CausalEvent.hpp"

namespace svqa
{
    class StartEvent : public CausalEvent
    {
        public:
            typedef std::shared_ptr<StartEvent> Ptr;
        
            StartEvent() : CausalEvent(0) {};
            virtual ~StartEvent() {};
        
            virtual CausalEventType getType()
            {
                return Start_Event;
            }
    };
}

#endif /* StartEvent_hpp */
