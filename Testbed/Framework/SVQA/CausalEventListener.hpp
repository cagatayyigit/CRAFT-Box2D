//
//  CausalEventListener.hpp
//  Testbed
//
//  Created by Tayfun Ateş on 28.01.2020.
//

#ifndef CausalEventListener_hpp
#define CausalEventListener_hpp

#include "Simulation.h"
#include "CausalEvent.hpp"

namespace svqa {
    class CausalEventListener
    {
        //Must be static. Cannot create object of this class
    public:
        static std::vector<CausalEvent::Ptr> getCurrentEvents(const int& step, WORLD* world);
        
    private:
        CausalEventListener();
        CausalEventListener(const CausalEventListener&);
        ~CausalEventListener();
    };
}

#endif /* CausalEventListener_hpp */
