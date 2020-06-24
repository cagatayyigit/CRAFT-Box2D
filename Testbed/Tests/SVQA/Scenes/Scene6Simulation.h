#pragma once

#include "Scene6Settings.h"
#include "SimulationBase.h"
#include "Box2D/Extension/b2VisBody.hpp"
#include "Box2D/Extension/b2VisPolygonShape.hpp"
#include <math.h> 

namespace svqa {
	class Scene6Simulation : public SimulationBase
	{
	public:
		typedef std::shared_ptr<Scene6Simulation> Ptr;
		Scene6Simulation(Scene6Settings::Ptr settings) : SimulationBase(settings)
		{
			m_nNumberOfObjects = settings->numberOfObjects;
			m_nNumberOfObstacles = settings->numberOfObstacles;

			SET_FILE_OUTPUT_TRUE(m_pSettings->outputVideoPath)
		}

		virtual SimulationID getIdentifier() override
		{
			return SimulationID::ID_Scene6;
		}

		void InitializeScene() override {

			
			// Basket
			// make x coord. random
			AddTargetBasket(b2Vec2(RandomFloatFromHardware(5.0, 10.0), -1.2f), 0.0f);


			//left
			// make angle random
			AddStaticObject(b2Vec2(-12.0f, 28.0f), 5*  M_PI  / RandomFloatFromHardware(5.5, 7.0), SimulationObject::STATIC_PLATFORM);


			// make y-coord random
			AddRandomDynamicObject(
				b2Vec2(-12.0f, 31.0f),
				b2Vec2(0.0f, -15.0f)
			);

			
			//right
			// make angle random
			AddStaticObject(b2Vec2(16.0f, 14.0f), - 15 * M_PI / RandomFloatFromHardware(19.0, 16.0), SimulationObject::STATIC_PLATFORM);

			
			// mid
			// make y-coord random
			float y = RandomFloatFromHardware(17.0, 20.0);
			AddStaticObject(b2Vec2(5.0f, y), M_PI, SimulationObject::STATIC_PLATFORM);


			// make x coord. random
			// make Velocity random
			AddRandomDynamicObject(
				b2Vec2(4.0f, y + 2.0f),
				b2Vec2(-8.0f, 0.0f),
				SimulationObject::CIRCLE
			);


			// bottom
			float32 h = RandomFloatFromHardware(9.0, 3.0); // make y-coords random
			AddStaticObject(b2Vec2(-5.0f, h),  M_PI , SimulationObject::STATIC_PLATFORM);
			AddStaticObject(b2Vec2(-19.0f, h),  M_PI , SimulationObject::STATIC_PLATFORM);


			AddRandomDynamicObject(
				b2Vec2(RandomFloatFromHardware(-20.0, -16.0), h + 2.0f),  // make x coord. random
				b2Vec2(RandomFloatFromHardware(8.0, 3.0), 0.0f),     // make x-velocity random
				SimulationObject::CIRCLE
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
