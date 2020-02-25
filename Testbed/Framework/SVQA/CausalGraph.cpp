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
        //Root is the start event
        auto eventQueue = m_EventQueue;
        CausalEvent::Ptr root = eventQueue.top();
        eventQueue.pop();
        
        while(!eventQueue.empty()) {
            const auto& event = eventQueue.top();
            addEventsToCausalGraph(root, event);
            eventQueue.pop();
        }
        
//        for(auto obj : m_ObjectEvents) {
//            const auto& events = obj.second;
//            for(auto event : events) {
//                std::cout << event->getStepCount() << " " <<event->getTypeStr() << std::endl;
//            }
//            std::cout << "************************************" << std::endl;
//        }
        
        std::cout << createGraphString() << std::endl;
    }

    CausalEvent::Ptr CausalGraph::getLatestEvent(BODY* object)
    {
        const auto& events = m_ObjectEvents[object];
        if(events.size()) {
            return events[events.size()-1];
        }
        return nullptr;
    }

    CausalEvent::Ptr CausalGraph::getLatestEventBeforeTimeStep(BODY* object, int step)
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

    void CausalGraph::addEventsToCausalGraph(CausalEvent::Ptr root, CausalEvent::Ptr newEvent)
    {
        if(newEvent->getType() == Start_Event) {
            return;
        }
        else if(newEvent->getType() == End_Event) {
            for(auto objEvents : m_ObjectEvents) {
                const auto& latestEventOfObject = getLatestEvent(objEvents.first);
                //Must not be null: for each object there should at least one event before end event
                newEvent->addCauseEvent(latestEventOfObject);
            }
            return;
        }
        const auto& newEventObjects = newEvent->getObjects();
        
        bool firstEventOfObject = true;
        for(auto neObj : newEventObjects) {
            if(! (neObj->GetType() == b2_staticBody) ) {
                const auto& latestEventOfObject = getLatestEventBeforeTimeStep(neObj, newEvent->getStepCount());
                if(latestEventOfObject) {
                    newEvent->addCauseEvent(latestEventOfObject);
                    firstEventOfObject = false;
                }
            }
        }
        
        if(firstEventOfObject) {
            newEvent->addCauseEvent(root);
        }
    }

    void addNodeToString(CausalEvent::Ptr event, std::string& str)
    {
        str += (std::to_string((long long)event.get()) + " [label=\"" + event->getStrRepresentation() + "\"]\n");
    }

    void addEdgesToString(CausalEvent::Ptr event, std::string& str, std::set<CausalEvent::Ptr>& visited)
    {
        const auto& neighbors = event->getImmediateOutcomes();
        
        str += (std::to_string((long long)event.get()) + " -> { ") ;
        for(auto ne : neighbors) {
            str += (std::to_string((long long)ne.get()) + " ") ;
        }
        str += "}\n";
        
        visited.insert(event);
        for(auto ne : neighbors) {
            if(visited.find(ne) == visited.end()) {
                addEdgesToString(ne, str, visited);
            }
        }
    }

    std::string CausalGraph::createGraphString()
    {
        std::string ret = "digraph d {\n";
        
        auto eventQueue = m_EventQueue;
        CausalEvent::Ptr root = eventQueue.top();
        addNodeToString(root,  ret);
        eventQueue.pop();
        
        while(!eventQueue.empty()) {

            const auto& event = eventQueue.top();
            addNodeToString(event,  ret);
            eventQueue.pop();
        }

        std::set<CausalEvent::Ptr> visited;
        addEdgesToString(root, ret, visited);
        
        ret += "}\n";
        return ret;
    }
}

