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
        
            StartEvent() : CausalEvent(-1) {};
            virtual ~StartEvent() {};
        
            static Ptr create()
            {
                return std::make_shared<StartEvent>();
            }
        
            virtual CausalEventType getType() override
            {
                return Start_Event;
            }
        
            virtual std::vector<CausalObject::Ptr> getObjects() override
            {
                std::vector<CausalObject::Ptr> ret;
                return ret;
            }
    };
}

#endif /* StartEvent_hpp */
