//
//  b2VisBody.cpp
//  Box2D
//
//  Created by Tayfun Ateş on 5.10.2019.
//

#include "b2VisBody.hpp"
#include "Box2D/Box2D.h"

b2VisBody::b2VisBody(const b2BodyDef* bd, b2World* world) : b2Body(bd, world)
{
    setColor(b2Color(1.0f, 1.0f, 1.0f, 1.0f));
}

b2VisBody::~b2VisBody()
{
    
}

b2Color b2VisBody::getColor() const
{
    return m_Color;
}

void b2VisBody::setColor(const b2Color& col)
{
    m_Color = col;
}

void b2VisBody::setPrevBody(b2VisBody* body)
{
    m_prev = body;
}

void b2VisBody::setNextBody(b2VisBody* body)
{
    m_next = body;
}

b2VisTexture::Ptr b2VisBody::getTexture() const
{
    return m_pTexture;
}

void b2VisBody::setTexture(b2VisTexture::Ptr tex)
{
    m_pTexture = tex;
}

bool b2VisBody::hasAttachedTexture() const
{
    return m_pTexture.get() != nullptr && m_pTexture->getTextureId()>0;
}


