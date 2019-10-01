//
//  RemoveObjectSimulation.h
//  Testbed
//
//  Created by Tayfun Ateş on 1.10.2019.
//

#ifndef RemoveObjectSimulation_h
#define RemoveObjectSimulation_h

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
        m_nNumberOfObjects = 10;
        m_nSimulationState = SS_CREATE_SCENE;
        m_vThrowMin = b2Vec2(-5.0f, 3.0f);
        m_vThrowMax = b2Vec2(5.0f, 7.0f);
        
        {
            b2BodyDef bd;
            b2Body* ground = m_world->CreateBody(&bd);

            b2EdgeShape shape;
            shape.Set(b2Vec2(-40.0f, 0.0f), b2Vec2(40.0f, 0.0f));
            ground->CreateFixture(&shape, 0.0f);
        }

        {
            for (int32 i = 0; i < m_nNumberOfObjects; ++i)
            {
                addSimulationObject();
            }
        }
    }

    void Step(Settings* settings)
    {
        Test::Step(settings);

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
        b2Body* body = m_world->CreateBody(&bd);
        body->CreateFixture(&shape, 5.0f);
    }

public:
    static Test* Create()
    {
        return new RemoveObjectSimulation;
    }
};

#endif /* RemoveObjectSimulation_h */
