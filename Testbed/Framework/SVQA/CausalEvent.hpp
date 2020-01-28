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
        
            virtual CausalEventType getType() = 0;
        
        private:
            int m_nStepCount;
        
    };
}

#endif /* CausalEdge_hpp */
