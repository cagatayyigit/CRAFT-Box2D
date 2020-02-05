//
//  CausalGraph.cpp
//  Testbed
//
//  Created by Tayfun Ateş on 28.01.2020.
//

#include "CausalGraph.hpp"
#include <algorithm>

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
        CausalEvent::Ptr root = nullptr;
        while(!m_EventQueue.empty()) {
            const auto& event = m_EventQueue.top();
            root = addEventsToCausalGraph(root, event);
            m_EventQueue.pop();
        }
        
        
//        for(auto obj : m_ObjectEvents) {
//            const auto& events = obj.second;
//            for(auto event : events) {
//                std::cout << event->getStepCount() << " " <<event->getTypeStr() << std::endl;
//            }
//            std::cout << "************************************" << std::endl;
//        }
        printEventQueue(m_EventQueue);
    }

    CausalEvent::Ptr CausalGraph::getLatestEventBeforeTimeStep(b2Body* object, int step)
    {
        const auto& events = m_ObjectEvents[object];
        
        if(events.size()) {
            auto prevEvent = events[0];
            if(prevEvent->getStepCount()<step) {
                //We are sure that there are at least two events here
                int i=1;
                auto nextEvent = events[i];
                
                while (nextEvent->getStepCount()<step) {
                    prevEvent = nextEvent;
                    nextEvent = events[++i];
                }
                
                return prevEvent;
            }
        }
        
        return nullptr;
    }

    CausalEvent::Ptr CausalGraph::addEventsToCausalGraph(CausalEvent::Ptr root, CausalEvent::Ptr newEvent)
    {
        if(!root) {
            return newEvent;
        }
        const auto& newEventObjects = newEvent->getObjects();
        
        bool firstEventOfObject = true;
        for(auto neObj : newEventObjects) {
            const auto& latestEventOfObject = getLatestEventBeforeTimeStep(neObj, newEvent->getStepCount());
            if(latestEventOfObject) {
                newEvent->addCauseEvent(latestEventOfObject);
                firstEventOfObject = false;
            }
        }
        
        if(firstEventOfObject) {
            newEvent->addCauseEvent(root);
        }
        
        return root;
    }

    
}

