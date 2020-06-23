#pragma once

#include "Scene10Settings.h"
#include "SimulationBase.h"
#include "Box2D/Extension/b2VisBody.hpp"
#include "Box2D/Extension/b2VisPolygonShape.hpp"
#include <math.h> 

namespace svqa {
    class Scene10Simulation : public SimulationBase
    {
    public:
        typedef std::shared_ptr<Scene10Simulation> Ptr;
        Scene10Simulation(Scene10Settings::Ptr settings) : SimulationBase(settings)
        {
            m_nNumberOfObjects = settings->numberOfObjects;
            m_nNumberOfObstacles = settings->numberOfObstacles;

            SET_FILE_OUTPUT_TRUE(m_pSettings->outputVideoPath)
        }

        virtual SimulationID getIdentifier() override
        {
            return SimulationID::ID_Scene10;
        }

        void InitializeScene() override {

        }

    private:

        bool m_bObstaclesCreated;
        int m_nNumberOfObjects;
        int m_nNumberOfObstacles;
        float32 m_fSpeed;
        b2Vec2 m_vMovingObjPosition;
        b2Vec2 m_vStagnantObjPosition;
        b2Vec2 m_vObstaclePosition;
        b2Vec2 m_vInitialDropVelocity;
    };
}
