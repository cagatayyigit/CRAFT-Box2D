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
        
            static Ptr create(const int& step, const CausalObject::Ptr& firstObject, const CausalObject::Ptr& secondObject)
            {
                return std::make_shared<StartTouchingEvent>(step, firstObject, secondObject);
            }
        
            virtual CausalEventType getType() override
            {
                return StartTouching_Event;
            }
        
            virtual std::vector<CausalObject::Ptr> getObjects() override
            {
                std::vector<CausalObject::Ptr> ret{ m_pFirstObject, m_pSecondObject };
                return ret;
            }
        
        private:
            CausalObject::Ptr   m_pFirstObject;
            CausalObject::Ptr   m_pSecondObject;
    };
}

#endif /* StartTouchingEvent_hpp */
