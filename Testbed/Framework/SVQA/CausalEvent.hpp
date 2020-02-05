//
//  CausalEdge.hpp
//  Testbed
//
//  Created by Tayfun Ateş on 28.01.2020.
//

#ifndef CausalEdge_hpp
#define CausalEdge_hpp

#include "CausalEventType.h"
#include "ObjectState.h"
#include <set>

namespace svqa
{
    struct EventOrder;
    
    class CausalEvent : public std::enable_shared_from_this<CausalEvent>
    {
        public:
            typedef std::shared_ptr<CausalEvent> Ptr;
        
            struct Order
            {
              bool operator()(const CausalEvent::Ptr& lhs, const CausalEvent::Ptr& rhs) const
              {
                return lhs->getStepCount() > rhs->getStepCount();
              }
            };
        
            typedef std::set<CausalEvent::Ptr> EventSet;
        
            CausalEvent(const int& step) : m_nStepCount(step) {};
            virtual ~CausalEvent() {};
        
            //Gets event type
            virtual CausalEventType getType() = 0;
        
            //Gets event's string type
            std::string getTypeStr()
            {
                return getTypeString(getType());
            }
        
            virtual std::string getStrRepresentation()
            {
                return getTypeStr() + ":" + std::to_string(m_nStepCount);
            }
        
            void addCauseEvent(CausalEvent::Ptr causeEvent) {
                this->m_vCauseEvents.insert(causeEvent);
                causeEvent->addOutcomeEvent(shared_from_this());
            }
        
            EventSet getImmediateOutcomes()
            {
                return m_vOutcomeEvents;
            }
        
            //Gets effected objects
            virtual std::vector<b2Body*> getObjects() = 0;
        
            //Get event's step count
            int getStepCount() const;
        
        private:
        
            void addOutcomeEvent(CausalEvent::Ptr outcomeEvent) {
                m_vOutcomeEvents.insert(outcomeEvent);
            }
        
            int                             m_nStepCount;
            EventSet                        m_vOutcomeEvents;
            EventSet                        m_vCauseEvents;
        
    };
}

#endif /* CausalEdge_hpp */
