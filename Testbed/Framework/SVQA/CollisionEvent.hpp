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
        
            CollisionEvent(const int& step, b2Body* firstObject, b2Body* secondObject) : CausalEvent(step), m_pFirstObject(firstObject), m_pSecondObject(secondObject) {};
            virtual ~CollisionEvent() {};
        
            static Ptr create(const int& step, b2Body* firstObject, b2Body* secondObject)
            {
                return std::make_shared<CollisionEvent>(step, firstObject, secondObject);
            }
        
            virtual CausalEventType getType() override
            {
                return Collision_Event;
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

#endif /* CollisionEvent_hpp */
