#pragma once

#include "Scene3Settings.h"
#include "SimulationBase.h"
#include "Box2D/Extension/b2VisBody.hpp"
#include "Box2D/Extension/b2VisPolygonShape.hpp"
#include <math.h> 

namespace svqa {
	class Scene3Simulation : public SimulationBase
	{
	public:
		typedef std::shared_ptr<Scene3Simulation> Ptr;
		Scene3Simulation(Scene3Settings::Ptr settings) : SimulationBase(settings)
		{
			m_nNumberOfObjects = settings->numberOfObjects;
			m_nNumberOfObstacles = settings->numberOfObstacles;

			SET_FILE_OUTPUT_TRUE(m_pSettings->outputVideoPath)
		}

		virtual SimulationID getIdentifier() override
		{
			return SimulationID::ID_Scene3;
		}

		void InitializeScene() override {

			
			// Basket
			AddTargetBasket(b2Vec2(21.0f, -1.2f), 0.0f);

			
			AddRandomDynamicObject(
				b2Vec2(-18.0f, RandomFloatFromHardware(26.0f, 35.0f)),
				b2Vec2(0.0f, 0.0f)
			);
			// ------- Inclined Platform-------
			AddStaticObject(b2Vec2(-13.0f, 19.2f), 4 * M_PI / 5, SimulationObject::STATIC_PLATFORM);
			

			



			AddRandomDynamicObject(
				b2Vec2(-18.0f, 11.2f),
				b2Vec2(RandomFloatFromHardware(5.0f, 10.0f), 0.0f),
				0b100,
				SimulationObject::Shape::CIRCLE);


			// ------- Top Platform-------
			AddStaticObject(b2Vec2(-12.0f, 9.2f), 0, SimulationObject::STATIC_PLATFORM);
			AddStaticObject(b2Vec2(RandomFloatFromHardware(8.0f, 13.0f), 9.2f), 0, SimulationObject::STATIC_PLATFORM);
		


			float32 bottomHeight = RandomFloatFromHardware(1.0f, 4.0f);
			AddRandomDynamicObject(
				b2Vec2(-18.0f, bottomHeight + 2.0f),
				b2Vec2(RandomFloatFromHardware(5.0f, 10.0f), 0.0f),
				0b100,
				SimulationObject::Shape::CIRCLE);



			// ------- Bottom Platform -------
			AddStaticObject(b2Vec2(-10.0f, bottomHeight), 0, SimulationObject::STATIC_PLATFORM);
			AddStaticObject(b2Vec2(-2.0f, bottomHeight), 0, SimulationObject::STATIC_PLATFORM);
			AddStaticObject(b2Vec2(9.5f, bottomHeight), 0, SimulationObject::STATIC_PLATFORM);

			
			



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
