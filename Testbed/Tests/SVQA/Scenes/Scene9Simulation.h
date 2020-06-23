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


			// top
			AddStaticObject(b2Vec2(7.0f, 29.5f), M_PI, SimulationObject::STATIC_PLATFORM);
			AddStaticObject(b2Vec2(-7.0f, 29.5f), M_PI, SimulationObject::STATIC_PLATFORM);

			AddRandomDynamicObject(
				b2Vec2(2.5f, 32.0f),
				b2Vec2(15.0f, 0.0f),
				SimulationObject::CIRCLE
			);

			AddRandomDynamicObject(
				b2Vec2(-1.5f, 32.0f),
				b2Vec2(-30.0f, 0.0f),
				SimulationObject::CIRCLE
			);
		

			AddStaticObject(b2Vec2(-17.0f, 24.5f),  8 * M_PI / 9, SimulationObject::STATIC_PLATFORM);
			AddStaticObject(b2Vec2(17.0f, 24.5f), - 8 * M_PI / 9, SimulationObject::STATIC_PLATFORM);





			// mid
			AddStaticObject(b2Vec2(5.0f, 15.5f), M_PI, SimulationObject::STATIC_PLATFORM);
			AddStaticObject(b2Vec2(-5.0f, 15.5f), M_PI, SimulationObject::STATIC_PLATFORM);
			AddRandomDynamicObject(
				b2Vec2(-8.0f, 17.0f),
				b2Vec2(0.0f, 0.0f)
			);
			AddRandomDynamicObject(
				b2Vec2(8.0f, 17.0f),
				b2Vec2(0.0f, 0.0f)
			);


			AddStaticObject(b2Vec2(-13.0f, 5.5f), 8 * M_PI / 9, SimulationObject::STATIC_PLATFORM);
			AddStaticObject(b2Vec2(13.0f, 5.5f), -8 * M_PI / 9, SimulationObject::STATIC_PLATFORM);
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
