//
//  RemoveObjectSimulation.h
//  Testbed
//
//  Created by Tayfun Ateş on 1.10.2019.
//

#ifndef RemoveObjectSimulation_h
#define RemoveObjectSimulation_h

#include "SimulationColor.h"
#include "Box2D/Extension/b2VisBody.hpp"

class RemoveObjectSimulation : public Test
{
public:
    enum SimulationState
    {
        SS_CREATE_SCENE = 0,
        SS_CREATE_FINAL_UNSTABLE = 1,
        SS_CREATE_FINAL_STABLE = 2,
        SS_SEGMENTATION_SCREENSHOT = 3
    };
    
    RemoveObjectSimulation()
    {
        m_nNumberOfObjects = 15;
        m_nSimulationState = SS_CREATE_SCENE;
        m_vThrowMin = b2Vec2(-3.0f, 3.0f);
        m_vThrowMax = b2Vec2(3.0f, 7.0f);
        m_nDistinctColorUsed = 8;
        
        {
            b2BodyDef bd;
            b2Body* ground = m_world->CreateBody(&bd);

            b2EdgeShape shape;
            shape.Set(b2Vec2(-40.0f, 0.0f), b2Vec2(40.0f, 0.0f));
            ground->CreateFixture(&shape, 0.0f);
        }
    }

    void Step(Settings* settings)
    {
        Test::Step(settings);
        
        if(isSceneStable() && m_nNumberOfObjects>0) {
            addSimulationObject();
            m_nNumberOfObjects--;
        }

        //b2DynamicTree* tree = &m_world->m_contactManager.m_broadPhase.m_tree;

        //if (m_stepCount == 400)
        //{
        //    tree->RebuildBottomUp();
        //}
    }
    
private:
    unsigned int m_nNumberOfObjects;
    SimulationState m_nSimulationState;
    b2Vec2 m_vThrowMin;
    b2Vec2 m_vThrowMax;
    unsigned short m_nDistinctColorUsed;

    void addSimulationObject()
    {
        float posX = RandomFloat(m_vThrowMin.x, m_vThrowMax.x);
        float posY = RandomFloat(m_vThrowMin.y, m_vThrowMax.y);
        
        float32 a = 0.5f;
        b2PolygonShape shape;
        shape.SetAsBox(a, a);
        
        b2BodyDef bd;
        bd.type = b2_dynamicBody;
        bd.position = b2Vec2(posX, posY);
        b2VisBody* body = (b2VisBody*) m_world->CreateBody(&bd);
        body->CreateFixture(&shape, 5.0f);
        
        int colorIndex = (rand() & (RAND_LIMIT)) % m_nDistinctColorUsed;
        SimulationColor col = SimulationColor((SimulationColor::TYPE) colorIndex);
        
        body->setColor(col.GetColor(SimulationMaterial::METAL));
    }
    
    bool isSceneStable()
    {
        b2Body* bodies = m_world->GetBodyList();
        for (b2Body* b = bodies; b; b = b->GetNext())
        {
            if(b->IsAwake() && !(b->GetType() == b2_staticBody)) {
                return false;
            }
        }
        return true;
    }

public:
    static Test* Create()
    {
        return new RemoveObjectSimulation;
    }
};

#endif /* RemoveObjectSimulation_h */
