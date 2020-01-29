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
        
            static Ptr create(const int& step, const CausalObject::Ptr& firstObject, const CausalObject::Ptr& secondObject)
            {
                return std::make_shared<EndTouchingEvent>(step, firstObject, secondObject);
            }
        
            virtual CausalEventType getType() override
            {
                return EndTouching_Event;
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

#endif /* EndTouchingEvent_hpp */
