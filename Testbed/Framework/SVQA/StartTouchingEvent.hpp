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
        
            StartTouchingEvent(const int& step, b2Body* firstObject, b2Body* secondObject) : CausalEvent(step), m_pFirstObject(firstObject), m_pSecondObject(secondObject) {};
            virtual ~StartTouchingEvent() {};
        
            static Ptr create(const int& step, b2Body* firstObject, b2Body* secondObject)
            {
                return std::make_shared<StartTouchingEvent>(step, firstObject, secondObject);
            }
        
            virtual CausalEventType getType() override
            {
                return StartTouching_Event;
            }
        
            virtual std::vector<b2Body*> getObjects() override
            {
                std::vector<b2Body*> ret{ m_pFirstObject, m_pSecondObject };
                return ret;
            }
        
        private:
            b2Body*   m_pFirstObject;
            b2Body*   m_pSecondObject;
    };
}

#endif /* StartTouchingEvent_hpp */
