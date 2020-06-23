#pragma once

#include "Scene7Settings.h"
#include "SimulationBase.h"
#include "Box2D/Extension/b2VisBody.hpp"
#include "Box2D/Extension/b2VisPolygonShape.hpp"
#include <math.h> 

namespace svqa {
	class Scene7Simulation : public SimulationBase
	{
	public:
		typedef std::shared_ptr<Scene7Simulation> Ptr;
		Scene7Simulation(Scene7Settings::Ptr settings) : SimulationBase(settings)
		{
			m_nNumberOfObjects = settings->numberOfObjects;
			m_nNumberOfObstacles = settings->numberOfObstacles;

			SET_FILE_OUTPUT_TRUE(m_pSettings->outputVideoPath)
		}

		virtual SimulationID getIdentifier() override
		{
			return SimulationID::ID_Scene7;
		}

		void InitializeScene() override {

			
			
			// Basket
			AddTargetBasket(b2Vec2(20.0f, -1.2f), 0.0f);




			//left
			AddStaticObject(b2Vec2(-13.0f, 17.0f), 7 * M_PI / 8, SimulationObject::STATIC_PLATFORM);
			AddStaticObject(b2Vec2(  7.0f, 9.0f), 7 * M_PI / 8, SimulationObject::STATIC_PLATFORM);

			AddRandomDynamicObject(
				b2Vec2(-12.0f, 25.0f),
				b2Vec2(0.0f, 0.0f)
			);

			


			
			// mid
			AddStaticObject(b2Vec2(-10.0f, 8.5f), M_PI, SimulationObject::STATIC_PLATFORM);
			AddDynamicObject(
				b2Vec2(-12.0f, 11.0f),
				b2Vec2(5.0f, 0.0f),
				SimulationObject::CIRCLE,
				SimulationObject::RED,
				SimulationObject::LARGE
			);

	

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
