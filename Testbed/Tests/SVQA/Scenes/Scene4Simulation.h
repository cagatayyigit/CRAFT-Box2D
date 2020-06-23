#pragma once

#include "Scene4Settings.h"
#include "SimulationBase.h"
#include "Box2D/Extension/b2VisBody.hpp"
#include "Box2D/Extension/b2VisPolygonShape.hpp"
#include <math.h> 

namespace svqa {
	class Scene4Simulation : public SimulationBase
	{
	public:
		typedef std::shared_ptr<Scene4Simulation> Ptr;
		Scene4Simulation(Scene4Settings::Ptr settings) : SimulationBase(settings)
		{
			m_nNumberOfObjects = settings->numberOfObjects;
			m_nNumberOfObstacles = settings->numberOfObstacles;

			SET_FILE_OUTPUT_TRUE(m_pSettings->outputVideoPath)
		}

		virtual SimulationID getIdentifier() override
		{
			return SimulationID::ID_Scene4;
		}

		void InitializeScene() override {

			
			
			// Basket
			AddTargetBasket(b2Vec2(21.0f, -1.2f), 0.0f);



			AddRandomDynamicObject(
				b2Vec2(RandomFloatFromHardware(-17.0f, -15.0f), 24.5f),
				b2Vec2(RandomFloatFromHardware(5.0f, 15.0f), 0.0f),
				SimulationObject::Shape::CIRCLE
				);
			AddStaticObject(b2Vec2(-18.0f, 23.0f), 0, SimulationObject::STATIC_PLATFORM);
			AddStaticObject(b2Vec2(-8.0f, 23.0f), 0, SimulationObject::STATIC_PLATFORM);
			AddStaticObject(b2Vec2(-2.0f, 23.0f), 0, SimulationObject::STATIC_PLATFORM);



			AddRandomDynamicObject(
				b2Vec2(RandomFloatFromHardware(-18.0f, -16.0f), 17.8f),
				b2Vec2(RandomFloatFromHardware(5.0f, 15.0f), 0.0f),
				SimulationObject::Shape::CIRCLE);

			AddStaticObject(b2Vec2(-18.0f, 16.0f), 0, SimulationObject::STATIC_PLATFORM);
			AddStaticObject(b2Vec2(-9.0f, 16.0f), 0, SimulationObject::STATIC_PLATFORM);





			AddRandomDynamicObject(
				b2Vec2(RandomFloatFromHardware(-18.0f, -17.0f), 11.5f),
				b2Vec2(RandomFloatFromHardware(5.0f, 15.0f), 0.0f),
				SimulationObject::Shape::CIRCLE
				);
			AddStaticObject(b2Vec2(-18.0f, 10.0f), 0, SimulationObject::STATIC_PLATFORM);



			AddRandomDynamicObject(
				b2Vec2(-18.0f, 5.5f),
				b2Vec2(RandomFloatFromHardware(5.0f, 15.0f), 0.0f),
				SimulationObject::Shape::CIRCLE
			);
			AddStaticObject(b2Vec2(-18.0f, 4.0f), 0, SimulationObject::STATIC_PLATFORM);
			AddStaticObject(b2Vec2(-4.0f, 4.0f), 0, SimulationObject::STATIC_PLATFORM);
			AddStaticObject(b2Vec2(9.5f, 4.0f), 0, SimulationObject::STATIC_PLATFORM);
			

			
			



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
