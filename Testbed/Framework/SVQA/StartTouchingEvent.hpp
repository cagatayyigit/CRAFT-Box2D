//
//  StartTouchingEvent.hpp
//  Testbed
//
//  Created by Tayfun Ateş on 28.01.2020.
//

#ifndef StartTouchingEvent_hpp
#define StartTouchingEvent_hpp

#include "CausalEvent.hpp"

namespace svqa
{
    class StartTouchingEvent : public CausalEvent
    {
        public:
            typedef std::shared_ptr<StartTouchingEvent> Ptr;
        
            StartTouchingEvent(const int& step, const CausalObject::Ptr& firstObject, const CausalObject::Ptr& secondObject) : CausalEvent(step), m_pFirstObject(firstObject), m_pSecondObject(secondObject) {};
            virtual ~StartTouchingEvent() {};
        
            virtual CausalEventType getType()
            {
                return StartTouching_Event;
            }
        
        private:
            CausalObject::Ptr   m_pFirstObject;
            CausalObject::Ptr   m_pSecondObject;
    };
}

#endif /* StartTouchingEvent_hpp */
