//
//  b2VisBody.hpp
//  Box2D
//
//  Created by Tayfun Ateş on 5.10.2019.
//

#ifndef b2VisBody_hpp
#define b2VisBody_hpp

#include "Box2D/Dynamics/b2Body.h"
#include "Box2D/Common/b2Draw.h"
#include "Box2D/Dynamics/b2World.h"

class b2VisBody : public b2Body
{
public:
    b2VisBody(const b2BodyDef* bd, b2World* world);
    
    
    virtual ~b2VisBody();
    
    //getters and setters
    b2Color getColor() const;
    void setColor(const b2Color& col);
    
protected:
    friend class b2VisWorld;
    
    //Sets previous body of this
    void setPrevBody(b2VisBody* body);
    
    //Sets next body of this
    void setNextBody(b2VisBody* body);
    
private:
    b2Color m_Color;
};


#endif /* b2VisBody_hpp */
