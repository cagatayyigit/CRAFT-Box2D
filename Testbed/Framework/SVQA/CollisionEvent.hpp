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
        
            CollisionEvent(const int& frame, const CausalObject::Ptr& firstObject, const CausalObject::Ptr& secondObject) : CausalEvent(frame), m_pFirstObject(firstObject), m_pSecondObject(secondObject) {};
            virtual ~CollisionEvent() {};
        
        private:
            CausalObject::Ptr   m_pFirstObject;
            CausalObject::Ptr   m_pSecondObject;
    };
}

#endif /* CollisionEvent_hpp */
