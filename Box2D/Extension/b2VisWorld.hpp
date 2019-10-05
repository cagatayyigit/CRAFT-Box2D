//
//  b2VisWorld.hpp
//  Box2D
//
//  Created by Tayfun Ateş on 5.10.2019.
//

#ifndef b2VisWorld_hpp
#define b2VisWorld_hpp

#include "Box2D/Dynamics/b2World.h"

class b2VisWorld : public b2World
{
public:
    b2VisWorld(const b2Vec2& gravity);
    virtual ~b2VisWorld();
    
    /// Create a rigid body given a definition. No reference to the definition
    /// is retained.
    /// @warning This function is locked during callbacks.
    virtual b2Body* CreateBody(const b2BodyDef* def);
    
    /// Call this to draw shapes and other debug draw data. This is intentionally non-const.
    virtual void DrawDebugData();

};

#endif /* b2VisWorld_hpp */
