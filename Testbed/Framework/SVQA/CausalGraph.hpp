//
//  CausalGraph.hpp
//  Testbed
//
//  Created by Tayfun Ateş on 28.01.2020.
//

#ifndef CausalGraph_hpp
#define CausalGraph_hpp

#include "CausalEvents.h"
#include <map>
#include <queue>
#include <iostream>

namespace svqa
{
    class CausalGraph
    {
        public:
            typedef std::shared_ptr<CausalGraph> Ptr;
        
            CausalGraph() {};
            virtual ~CausalGraph() {};
        
            static Ptr create()
            {
                return std::make_shared<CausalGraph>();
            }
        
            void addEvent(const CausalEvent::Ptr& event);
        
            template<typename T> void printEventQueue(T& q) {
                while(!q.empty()) {
                    std::cout << q.top()->getStepCount() << " " << q.top()->getTypeStr() << std::endl;;
                    q.pop();
                }
                std::cout << '\n';
            }
        
        private:
            StartEvent::Ptr                                                                         m_pStartEvent;      //Root of the graph
            EndEvent::Ptr                                                                           m_pEndEvent;        //Single leaf of the graph
            std::map<CausalObject::Ptr, std::vector<CausalEvent::Ptr> >                             m_ObjectEvents;     //Map of objects an their events
  
            std::priority_queue<CausalEvent::Ptr, std::vector<CausalEvent::Ptr>, EventOrder>        m_EventQueue;
        
            //Constructs causal graph from objects to events mapping
            void constructCausalGraph();
    };
}

#endif /* CausalGraph_hpp */
