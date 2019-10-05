//
//  b2VisWorld.cpp
//  Box2D
//
//  Created by Tayfun Ateş on 5.10.2019.
//

#include "b2VisWorld.hpp"
#include "Box2D/Dynamics/b2Body.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include "Box2D/Dynamics/b2Island.h"
#include "Box2D/Common/b2Draw.h"
#include "Box2D/Common/b2Timer.h"
#include "Box2D/Extension/b2VisBody.hpp"

b2VisWorld::b2VisWorld(const b2Vec2& gravity) : b2World(gravity)
{
    
}

b2VisWorld::~b2VisWorld()
{
    
}

b2Body* b2VisWorld::CreateBody(const b2BodyDef* def)
{
    b2Assert(IsLocked() == false);
    if (IsLocked())
    {
        return nullptr;
    }

    void* mem = m_blockAllocator.Allocate(sizeof(b2VisWorld));
    b2VisBody* b = new (mem) b2VisBody(def, this);

    // Add to world doubly linked list.
    b->setPrevBody(nullptr);
    b->setNextBody((b2VisBody*)m_bodyList);
    if (m_bodyList)
    {
        ((b2VisBody*) m_bodyList)->setPrevBody(b);
    }
    m_bodyList = b;
    ++m_bodyCount;

    return b;
}

void b2VisWorld::DrawDebugData()
{
    if (m_debugDraw == nullptr)
    {
        return;
    }

    uint32 flags = m_debugDraw->GetFlags();

    if (flags & b2Draw::e_shapeBit)
    {
        for (b2VisBody* b = (b2VisBody*) m_bodyList; b; b = (b2VisBody*) b->GetNext())
        {
            const b2Transform& xf = b->GetTransform();
            for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
            {
                if (b->IsActive() == false)
                {
                    DrawShape(f, xf, b2Color(0.5f, 0.5f, 0.3f));
                }
                else if (b->GetType() == b2_staticBody)
                {
                    DrawShape(f, xf, b2Color(0.5f, 0.9f, 0.5f));
                }
                else if (b->GetType() == b2_kinematicBody)
                {
                    DrawShape(f, xf, b2Color(0.5f, 0.5f, 0.9f));
                }
                else if (b->IsAwake() == false)
                {
                    DrawShape(f, xf, b->getColor());
                }
                else
                {
                    DrawShape(f, xf, b2Color(0.9f, 0.7f, 0.7f));
                }
            }
        }
    }

//    if (flags & b2Draw::e_jointBit)
//    {
//        for (b2Joint* j = m_jointList; j; j = j->GetNext())
//        {
//            DrawJoint(j);
//        }
//    }
//
//    if (flags & b2Draw::e_pairBit)
//    {
//        b2Color color(0.3f, 0.9f, 0.9f);
//        for (b2Contact* c = m_contactManager.m_contactList; c; c = c->GetNext())
//        {
//            //b2Fixture* fixtureA = c->GetFixtureA();
//            //b2Fixture* fixtureB = c->GetFixtureB();
//
//            //b2Vec2 cA = fixtureA->GetAABB().GetCenter();
//            //b2Vec2 cB = fixtureB->GetAABB().GetCenter();
//
//            //g_debugDraw->DrawSegment(cA, cB, color);
//        }
//    }

//    if (flags & b2Draw::e_aabbBit)
//    {
//        b2Color color(0.9f, 0.3f, 0.9f);
//        b2BroadPhase* bp = &m_contactManager.m_broadPhase;
//
//        for (b2Body* b = m_bodyList; b; b = b->GetNext())
//        {
//            if (b->IsActive() == false)
//            {
//                continue;
//            }
//
//            for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
//            {
//                for (int32 i = 0; i < f->m_proxyCount; ++i)
//                {
//                    b2FixtureProxy* proxy = f->m_proxies + i;
//                    b2AABB aabb = bp->GetFatAABB(proxy->proxyId);
//                    b2Vec2 vs[4];
//                    vs[0].Set(aabb.lowerBound.x, aabb.lowerBound.y);
//                    vs[1].Set(aabb.upperBound.x, aabb.lowerBound.y);
//                    vs[2].Set(aabb.upperBound.x, aabb.upperBound.y);
//                    vs[3].Set(aabb.lowerBound.x, aabb.upperBound.y);
//
//                    m_debugDraw->DrawPolygon(vs, 4, color);
//                }
//            }
//        }
//    }

//    if (flags & b2Draw::e_centerOfMassBit)
//    {
//        for (b2Body* b = m_bodyList; b; b = b->GetNext())
//        {
//            b2Transform xf = b->GetTransform();
//            xf.p = b->GetWorldCenter();
//            m_debugDraw->DrawTransform(xf);
//        }
//    }
}