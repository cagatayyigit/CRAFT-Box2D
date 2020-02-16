//
//  CausalEdge.cpp
//  Testbed
//
//  Created by Tayfun Ateş on 28.01.2020.
//

#include "CausalEvent.hpp"

namespace svqa
{
    int CausalEvent::getStepCount() const
    {
        return m_nStepCount;
    }

    std::string CausalEvent::getStrRepresentation()
    {
        std::string ret = getTypeStr() + ":" + std::to_string(m_nStepCount);
        auto objects = getObjects();
        for(auto& obj : objects) {
            ret += "-";
        }
        return ret;
    }
}
