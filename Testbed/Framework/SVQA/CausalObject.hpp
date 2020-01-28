//
//  CausalObject.hpp
//  Testbed
//
//  Created by Tayfun Ateş on 28.01.2020.
//

#ifndef CausalObject_hpp
#define CausalObject_hpp

#include <stdlib.h>
#include <memory>
#include "ObjectState.h"

namespace svqa
{
    class CausalObject
    {
        public:
            typedef std::shared_ptr<CausalObject> Ptr;
        
            CausalObject(BODY* body, const int& identifier) : m_pBody(body), m_nIdentifier(identifier) {};
            virtual ~CausalObject() {};
        
        private:
        
            BODY*               m_pBody;
            int                 m_nIdentifier;
    };
}


#endif /* CausalObject_hpp */
