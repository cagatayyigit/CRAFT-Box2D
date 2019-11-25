//
//  b2VisWorld.cpp
//  Box2D
//
//  Created by Tayfun Ateş on 5.10.2019.
//

#include "b2VisWorld.hpp"
#include "Box2D/Extension/b2VisBody.hpp"
#include "Box2D/Extension/b2VisPolygonShape.hpp"
#include "Box2D/Dynamics/b2World.h"
#include "Box2D/Dynamics/b2Body.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include "Box2D/Dynamics/b2Island.h"
#include "Box2D/Dynamics/Joints/b2PulleyJoint.h"
#include "Box2D/Dynamics/Contacts/b2Contact.h"
#include "Box2D/Dynamics/Contacts/b2ContactSolver.h"
#include "Box2D/Collision/b2Collision.h"
#include "Box2D/Collision/b2BroadPhase.h"
#include "Box2D/Collision/Shapes/b2CircleShape.h"
#include "Box2D/Collision/Shapes/b2EdgeShape.h"
#include "Box2D/Collision/Shapes/b2ChainShape.h"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Box2D/Collision/b2TimeOfImpact.h"
#include "Box2D/Common/b2Draw.h"
#include "Box2D/Common/b2Timer.h"


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

    void* mem = m_blockAllocator.Allocate(sizeof(b2VisBody));
    b2VisBody* b = new (mem) b2VisBody(def, this);

    // Add to world doubly linked list.
    b->m_prev = nullptr;
    b->m_next = m_bodyList;
    if (m_bodyList)
    {
        m_bodyList->m_prev = b;
    }
    m_bodyList = b;
    ++m_bodyCount;

    return b;
}

void b2VisWorld::DestroyBody(b2Body* b)
{
    b2Assert(m_bodyCount > 0);
    b2Assert(IsLocked() == false);
    if (IsLocked())
    {
        return;
    }

    // Delete the attached joints.
    b2JointEdge* je = b->m_jointList;
    while (je)
    {
        b2JointEdge* je0 = je;
        je = je->next;

        if (m_destructionListener)
        {
            m_destructionListener->SayGoodbye(je0->joint);
        }

        DestroyJoint(je0->joint);

        b->m_jointList = je;
    }
    b->m_jointList = nullptr;

    // Delete the attached contacts.
    b2ContactEdge* ce = b->m_contactList;
    while (ce)
    {
        b2ContactEdge* ce0 = ce;
        ce = ce->next;
        m_contactManager.Destroy(ce0->contact);
    }
    b->m_contactList = nullptr;

    // Delete the attached fixtures. This destroys broad-phase proxies.
    b2Fixture* f = b->m_fixtureList;
    while (f)
    {
        b2Fixture* f0 = f;
        f = f->m_next;

        if (m_destructionListener)
        {
            m_destructionListener->SayGoodbye(f0);
        }

        f0->DestroyProxies(&m_contactManager.m_broadPhase);
        f0->Destroy(&m_blockAllocator);
        f0->~b2Fixture();
        m_blockAllocator.Free(f0, sizeof(b2Fixture));

        b->m_fixtureList = f;
        b->m_fixtureCount -= 1;
    }
    b->m_fixtureList = nullptr;
    b->m_fixtureCount = 0;

    // Remove world body list.
    if (b->m_prev)
    {
        b->m_prev->m_next = b->m_next;
    }

    if (b->m_next)
    {
        b->m_next->m_prev = b->m_prev;
    }

    if (b == m_bodyList)
    {
        m_bodyList = b->m_next;
    }

    --m_bodyCount;
    ((b2VisBody*)b)->~b2VisBody();
    m_blockAllocator.Free(b, sizeof(b2VisBody));
}

void b2VisWorld::DrawTexturedShape(b2Fixture* fixture, const b2Transform& xf, const b2Color& color, const uint32& glTextureId, const int& textureMaterialId)
{
    switch (fixture->GetType())
    {
        //TODO: add other types of shapes

    case b2Shape::e_polygon:
        {
            b2VisPolygonShape* poly = (b2VisPolygonShape*)fixture->GetShape();
            int32 vertexCount = poly->m_count;
            b2Assert(vertexCount <= b2_maxPolygonVertices);
            b2Vec2 vertices[b2_maxPolygonVertices];

            for (int32 i = 0; i < vertexCount; ++i)
            {
                vertices[i] = b2Mul(xf, poly->m_vertices[i]);
            }
            std::vector<b2Vec2> texCoords = poly->getTextureCoords();
            
            m_debugDraw->DrawTexturedSolidPolygon(vertices, texCoords.data(), glTextureId, textureMaterialId, vertexCount, color);
        }
        break;
            
    default:
        break;
    }
}

b2Draw* b2VisWorld::getRenderer()
{
    return m_debugDraw;
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
                const auto texture = b->getTexture();
                if (b->IsActive() == false)
                {
                    DrawTexturedShape(f, xf, b2Color(0.5f, 0.5f, 0.3f), texture->getTextureId(), texture->getMaterialIndex());
                }
                else if (b->GetType() == b2_staticBody)
                {
                    if(texture) {
                        DrawTexturedShape(f, xf, b->getColor(), texture->getTextureId(), texture->getMaterialIndex());
                    } else {
                        DrawShape(f, xf, b2Color(0.5f, 0.9f, 0.5f));
                    }
                }
                else if (b->GetType() == b2_kinematicBody)
                {
                    if(texture) {
                          DrawTexturedShape(f, xf, b->getColor(), texture->getTextureId(), texture->getMaterialIndex());
                      } else {
                          DrawShape(f, xf, b2Color(0.5f, 0.5f, 0.9f));
                      }
                }
                else if (b->IsAwake() == false)
                {
                    if(texture) {
                        DrawTexturedShape(f, xf, b->getColor(), texture->getTextureId(), texture->getMaterialIndex());
                    } else {
                        DrawShape(f, xf, b->getColor());
                    }
                }
                else
                {
                    if(texture) {
                        DrawTexturedShape(f, xf, b2Color(0.9f, 0.7f, 0.7f), texture->getTextureId(), texture->getMaterialIndex());
                    } else {
                        DrawShape(f, xf, b->getColor());
                    }
                }
            }
        }
    }

    if (flags & b2Draw::e_jointBit)
    {
        for (b2Joint* j = m_jointList; j; j = j->GetNext())
        {
            DrawJoint(j);
        }
    }
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
