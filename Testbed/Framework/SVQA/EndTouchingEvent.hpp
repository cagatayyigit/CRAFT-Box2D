//
//  EndTouchingEvent.hpp
//  Testbed
//
//  Created by Tayfun Ateş on 28.01.2020.
//

#ifndef EndTouchingEvent_hpp
#define EndTouchingEvent_hpp

#include "CausalEvent.hpp"

namespace svqa
{
    class EndTouchingEvent : public CausalEvent
    {
        public:
            typedef std::shared_ptr<EndTouchingEvent> Ptr;
        
            EndTouchingEvent(const int& step, const CausalObject::Ptr& firstObject, const CausalObject::Ptr& secondObject) : CausalEvent(step), m_pFirstObject(firstObject), m_pSecondObject(secondObject) {};
            virtual ~EndTouchingEvent() {};
        
            virtual CausalEventType getType()
            {
                return EndTouching_Event;
            }
        
        private:
            CausalObject::Ptr   m_pFirstObject;
            CausalObject::Ptr   m_pSecondObject;
    };
}

#endif /* EndTouchingEvent_hpp */
