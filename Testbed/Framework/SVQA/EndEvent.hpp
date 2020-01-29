//
//  EndEvent.hpp
//  Testbed
//
//  Created by Tayfun Ateş on 29.01.2020.
//

#ifndef EndEvent_hpp
#define EndEvent_hpp

#include "CausalEvent.hpp"

namespace svqa
{
    class EndEvent : public CausalEvent
    {
        public:
            typedef std::shared_ptr<EndEvent> Ptr;
        
            EndEvent() : CausalEvent(0) {};
            virtual ~EndEvent() {};
        
            static Ptr create()
            {
                return std::make_shared<EndEvent>();
            }
        
            virtual CausalEventType getType() override
            {
                return End_Event;
            }
        
            virtual std::vector<CausalObject::Ptr> getObjects() override
            {
                std::vector<CausalObject::Ptr> ret;
                return ret;
            }
    };
}

#endif /* EndEvent_hpp */
