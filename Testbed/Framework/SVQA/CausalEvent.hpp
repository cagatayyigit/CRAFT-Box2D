//
//  CausalEdge.hpp
//  Testbed
//
//  Created by Tayfun Ateş on 28.01.2020.
//

#ifndef CausalEdge_hpp
#define CausalEdge_hpp

#include "CausalObject.hpp"
#include "CausalEventType.h"

namespace svqa
{
    class CausalEvent
    {
        public:
            typedef std::shared_ptr<CausalEvent> Ptr;
        
            CausalEvent(const int& step) : m_nStepCount(step) {};
            virtual ~CausalEvent() {};
        
            //Gets event type
            virtual CausalEventType getType() = 0;
        
            //Gets event's string type
            std::string getTypeStr()
            {
                return getTypeString(getType());
            }
        
            //Gets effected objects
            virtual std::vector<CausalObject::Ptr> getObjects() = 0;
        
            //Get event's step count
            int getStepCount() const;
        
        private:
            int m_nStepCount;
        
    };
}

#endif /* CausalEdge_hpp */
