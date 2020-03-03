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

    std::string CausalEvent::getStrRepresentation() // "StartTouching:59 - id: 3 sh: b_bound col: black - id: 2 sh: s_circle col: brown"
    {
            
        std::string eventType = getTypeStr() + ":" + std::to_string(m_nStepCount);  // "StartTouching:59"
        std::string imgPaths[2];                                          // "C:\Users\Cagatay\Desktop\graphviz\0.png"

        // <TD ><IMG SRC="C:\Users\Cagatay\Desktop\graphviz\0.png"/></TD>

        auto objects = getObjects();
        for(auto& obj : objects) {
            ObjectState* objState = (ObjectState*) obj->GetUserData();
            std::string imgPath = objState->getImagePath();
            imgPaths->append(imgPath);
        }
        
        std::string resultStr = "<<TABLE BORDER=\"0\" CELLBORDER=\"0\" CELLSPACING=\"0\">< TR ><TD >" + eventType + "< / TD>< / TR><TR>  <TD ><IMG SRC = "+ imgPaths[0]+"/ >< / TD>  <TD><IMG SRC =" + imgPaths[1] +"/ >< / TD>< / TR>< / TABLE >>  ";
        

        return resultStr;
    }
}
