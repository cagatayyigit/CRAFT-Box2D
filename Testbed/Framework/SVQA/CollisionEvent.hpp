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
        
            virtual CausalEventType getType()
            {
                return Collision_Event;
            }
        
        private:
            CausalObject::Ptr   m_pFirstObject;
            CausalObject::Ptr   m_pSecondObject;
    };
}

#endif /* CollisionEvent_hpp */
