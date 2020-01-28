//
//  CausalGraph.hpp
//  Testbed
//
//  Created by Tayfun Ateş on 28.01.2020.
//

#ifndef CausalGraph_hpp
#define CausalGraph_hpp

#include "CausalEvent.hpp"

namespace svqa
{
    class CausalGraph
    {
        public:
            typedef std::shared_ptr<CausalGraph> Ptr;
        
            CausalGraph() {};
            virtual ~CausalGraph() {};
        
            void addEdge(const CausalEvent::Ptr& edge);
    };
}

#endif /* CausalGraph_hpp */
