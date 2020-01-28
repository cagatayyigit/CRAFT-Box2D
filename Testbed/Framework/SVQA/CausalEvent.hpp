//
//  CausalEdge.hpp
//  Testbed
//
//  Created by Tayfun Ateş on 28.01.2020.
//

#ifndef CausalEdge_hpp
#define CausalEdge_hpp

#include "CausalObject.hpp"

namespace svqa
{
    class CausalEvent
    {
        public:
            typedef std::shared_ptr<CausalEvent> Ptr;
        
            CausalEvent(const int& frame) : m_nFrameIndex(frame) {};
            virtual ~CausalEvent() {};
        
        private:
            int m_nFrameIndex;
        
    };
}

#endif /* CausalEdge_hpp */
