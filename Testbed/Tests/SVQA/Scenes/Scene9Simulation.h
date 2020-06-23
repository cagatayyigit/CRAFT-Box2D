#pragma once

#include "Scene9Settings.h"
#include "SimulationBase.h"
#include "Box2D/Extension/b2VisBody.hpp"
#include "Box2D/Extension/b2VisPolygonShape.hpp"
#include <math.h> 

namespace svqa {
	class Scene9Simulation : public SimulationBase
	{
	public:
		typedef std::shared_ptr<Scene9Simulation> Ptr;
		Scene9Simulation(Scene9Settings::Ptr settings) : SimulationBase(settings)
		{
			m_nNumberOfObjects = settings->numberOfObjects;
			m_nNumberOfObstacles = settings->numberOfObstacles;

			SET_FILE_OUTPUT_TRUE(m_pSettings->outputVideoPath)
		}

		virtual SimulationID getIdentifier() override
		{
			return SimulationID::ID_Scene9;
		}

		void InitializeScene() override {
			// Basket
			AddTargetBasket(b2Vec2(0.0f, -1.2f), 0.0f);


			// Top Platform
			AddStaticObject(b2Vec2(7.0f, 29.5f), M_PI, SimulationObject::STATIC_PLATFORM);
			AddStaticObject(b2Vec2(-7.0f, 29.5f), M_PI, SimulationObject::STATIC_PLATFORM);

			AddRandomDynamicObject(
				b2Vec2(RandomFloat(1.5f, 12.5f), RandomFloat(30.5f, 32.0f)),
				b2Vec2(RandomFloat(30.0f, 5.0f), 0.0f),
				SimulationObject::CIRCLE
			);

			AddRandomDynamicObject(
				b2Vec2(-RandomFloat(1.5f, 12.5f), RandomFloat(30.5f, 32.0f)),
				b2Vec2(-RandomFloat(30.0f, 5.0f), 0.0f),
				SimulationObject::CIRCLE
			);
		

			AddStaticObject(b2Vec2(-RandomFloat(16,18), RandomFloat(24,25)), RandomFloat(7.5f, 8.5f) * M_PI / 9, SimulationObject::STATIC_PLATFORM);
			AddStaticObject(b2Vec2(RandomFloat(16, 18), RandomFloat(24, 25)), -RandomFloat(7.5f, 8.5f) * M_PI / 9, SimulationObject::STATIC_PLATFORM);


			// Middle Platform
			AddStaticObject(b2Vec2(5.0f, 15.5f), M_PI, SimulationObject::STATIC_PLATFORM);
			AddStaticObject(b2Vec2(-5.0f, 15.5f), M_PI, SimulationObject::STATIC_PLATFORM);

			AddRandomDynamicObject(
				b2Vec2(-RandomFloat(8.0f,12.0f), 17.0f),
				b2Vec2(0.0f, 0.0f)
			);
			AddRandomDynamicObject(
				b2Vec2(RandomFloat(8.0f, 12.0f), 17.0f),
				b2Vec2(0.0f, 0.0f)
			);


			AddStaticObject(b2Vec2(-RandomFloat(12, 14), RandomFloat(5, 6.5f)), RandomFloat(7.5f, 8.25f) * M_PI / 9, SimulationObject::STATIC_PLATFORM);
			AddStaticObject(b2Vec2(RandomFloat(12, 14), RandomFloat(5, 6.5f)), -RandomFloat(7.5f, 8.25f) * M_PI / 9, SimulationObject::STATIC_PLATFORM);
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
