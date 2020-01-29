//
//  CausalGraph.cpp
//  Testbed
//
//  Created by Tayfun Ateş on 28.01.2020.
//

#include "CausalGraph.hpp"

namespace svqa {
    void CausalGraph::addEvent(const CausalEvent::Ptr& event)
    {
        if(m_pEndEvent) {
            assert("End event is obtained! Cannot add more events");
            return;
        }
        
        const auto& eventType = event->getType();
        if(eventType == Start_Event) {
            if(m_pStartEvent) {
                assert("Graph already has a start graph");
            }
            m_pStartEvent = std::static_pointer_cast<StartEvent>(event);
        }
        
        if(eventType == End_Event) {
            m_pEndEvent = std::static_pointer_cast<EndEvent>(event);
        }
        
        const auto& effectedObjects = event->getObjects();
        for(auto object : effectedObjects) {
            m_ObjectEvents[object].push_back(event);
        }
    
        m_EventQueue.push(event);
        
        if(eventType == End_Event) {
            constructCausalGraph();
        }
    }

    void CausalGraph::constructCausalGraph()
    {
//        for(auto obj : m_ObjectEvents) {
//            const auto& events = obj.second;
//            for(auto event : events) {
//                std::cout << event->getStepCount() << " " <<event->getTypeStr() << std::endl;
//            }
//            std::cout << "************************************" << std::endl;
//        }
        printEventQueue(m_EventQueue);
    }
}

