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
        
            EndTouchingEvent(const int& step, b2Body* firstObject, b2Body* secondObject) : CausalEvent(step), m_pFirstObject(firstObject), m_pSecondObject(secondObject) {};
            virtual ~EndTouchingEvent() {};
        
            static Ptr create(const int& step, b2Body* firstObject, b2Body* secondObject)
            {
                return std::make_shared<EndTouchingEvent>(step, firstObject, secondObject);
            }
        
            virtual CausalEventType getType() override
            {
                return EndTouching_Event;
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

#endif /* EndTouchingEvent_hpp */
