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
        
            CausalObject(b2Body* body) : m_pBody(body) {};
            virtual ~CausalObject() {};
        
            static Ptr create(b2Body* body) {
                return std::make_shared<CausalObject>(body);
            }
        
        private:
        
            b2Body*               m_pBody;
    };
}


#endif /* CausalObject_hpp */
