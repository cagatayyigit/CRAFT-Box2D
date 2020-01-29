//
//  CollisionEvent.hpp
//  Testbed
//
//  Created by Tayfun Ateş on 28.01.2020.
//

#ifndef CollisionEvent_hpp
#define CollisionEvent_hpp

#include "CausalEvent.hpp"

namespace svqa
{
    class CollisionEvent : public CausalEvent
    {
        public:
            typedef std::shared_ptr<CollisionEvent> Ptr;
        
            CollisionEvent(const int& step, const CausalObject::Ptr& firstObject, const CausalObject::Ptr& secondObject) : CausalEvent(step), m_pFirstObject(firstObject), m_pSecondObject(secondObject) {};
            virtual ~CollisionEvent() {};
        
            static Ptr create(const int& step, const CausalObject::Ptr& firstObject, const CausalObject::Ptr& secondObject)
            {
                return std::make_shared<CollisionEvent>(step, firstObject, secondObject);
            }
        
            virtual CausalEventType getType() override
            {
                return Collision_Event;
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

#endif /* CollisionEvent_hpp */
