#pragma once

#include "SimulationColor.h"
#include "ObstructionDemoSettings.h"
#include "SimulationBase.h"
#include "Box2D/Extension/b2VisBody.hpp"
#include "Box2D/Extension/b2VisPolygonShape.hpp"
#include <math.h>

namespace svqa {
	class ObstructionDemoSimulation : public SimulationBase
	{
	public:
		typedef std::shared_ptr<ObstructionDemoSimulation> Ptr;

		ObstructionDemoSimulation(ObstructionDemoSettings::Ptr _settings_) : SimulationBase(_settings_)
		{
			m_nNumberOfObjects = _settings_->numberOfObjects;
			m_nNumberOfObstacles = _settings_->numberOfObstacles;

			m_fSpeed = RandomFloat(15.0f, 30.0f);

			m_vObstaclePosition = b2Vec2(RandomFloat(-10.0f, 10.0f), RandomFloat(15.0f, 40.0f));
			m_vMovingObjPosition = b2Vec2(RandomFloat(-25.0f, -10.0), 2.5f);
			m_vStagnantObjPosition = b2Vec2(RandomFloat(10.0f, 30.0f), 2.5f);

			m_vInitialDropVelocity = b2Vec2(0.0f, RandomFloat(-20.0f, -40.0f));

			SET_FILE_OUTPUT_TRUE(m_pSettings->outputFilePath)
		}

		virtual SimulationID getIdentifier() override
		{
			return SimulationID::ID_ObstructedPath;
		}

		void InitializeScene() override {
			AddSimulationObject(m_vMovingObjPosition, b2Vec2(m_fSpeed, 0.0f), SimulationObject::SMALL_CIRCLE, SimulationColor::TYPE::BROWN);

			AddSimulationObject(m_vObstaclePosition, m_vInitialDropVelocity, SimulationObject::BIG_CUBE, SimulationColor::TYPE::RED);

			AddSimulationObject(m_vStagnantObjPosition, b2Vec2_zero, SimulationObject::SMALL_CIRCLE, SimulationColor::TYPE::BLUE);
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
