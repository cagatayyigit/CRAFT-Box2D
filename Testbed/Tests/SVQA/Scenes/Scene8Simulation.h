#pragma once

#include "Scene8Settings.h"
#include "SimulationBase.h"
#include "Box2D/Extension/b2VisBody.hpp"
#include "Box2D/Extension/b2VisPolygonShape.hpp"
#include <math.h> 

namespace svqa {
	class Scene8Simulation : public SimulationBase
	{
	public:
		typedef std::shared_ptr<Scene8Simulation> Ptr;
		Scene8Simulation(Scene8Settings::Ptr settings) : SimulationBase(settings)
		{
			m_nNumberOfObjects = settings->numberOfObjects;
			m_nNumberOfObstacles = settings->numberOfObstacles;

			SET_FILE_OUTPUT_TRUE(m_pSettings->outputVideoPath)
		}

		virtual SimulationID getIdentifier() override
		{
			return SimulationID::ID_Scene8;
		}

		void InitializeScene() override {
			// TODO: Does not easily produce intended outcomes.
			//       We may need to change positions and orientations of dynamic objects,
			//       especially one at the top.

			// Basket
			AddTargetBasket(b2Vec2(RandomFloat(20, 21), RandomFloat(19, 20)), 0.0f);


			float topY = RandomFloat(29, 30);
			AddStaticObject(b2Vec2(RandomFloat(6, 8), topY), M_PI, SimulationObject::STATIC_PLATFORM);
			AddStaticObject(b2Vec2(-RandomFloat(-4, -2), topY), M_PI, SimulationObject::STATIC_PLATFORM);
			// TODO: Maybe change the direction of this object?
			AddRandomDynamicObject(
				b2Vec2(RandomFloat(10, 14), topY + 2.5f),
				b2Vec2(-RandomFloat(50, 75), 0.0f),
				0b100,
				SimulationObject::CIRCLE
			);



			// top
			topY = RandomFloat(22, 23);
			AddStaticObject(b2Vec2(-RandomFloat(16, 18), topY), M_PI, SimulationObject::STATIC_PLATFORM);
			AddStaticObject(b2Vec2(-RandomFloat(6, 8), topY), M_PI, SimulationObject::STATIC_PLATFORM);
		


			// mid
			AddStaticObject(b2Vec2(-RandomFloat(16, 18), RandomFloat(15, 16)), M_PI, SimulationObject::STATIC_PLATFORM);


			// bottom
			float bottomPlatformHeight = RandomFloat(6, 8.5f);
			float bottomLayeredRampHeight = bottomPlatformHeight + 4.6;

			auto layeredRampHeight = [bottomLayeredRampHeight](int layerCount) {
				float layerHeight = 3.25f;
				return bottomLayeredRampHeight + layerHeight * layerCount;
			};
			AddStaticObject(b2Vec2(-17.0f, bottomPlatformHeight), M_PI, SimulationObject::STATIC_PLATFORM);
			AddStaticObject(b2Vec2(-2.8f, layeredRampHeight(0)), -4 * M_PI / 5, SimulationObject::STATIC_PLATFORM);
			AddStaticObject(b2Vec2(3.3f, layeredRampHeight(1)), -4 * M_PI / 5, SimulationObject::STATIC_PLATFORM);
			AddStaticObject(b2Vec2(9.3f, layeredRampHeight(2)), -4 * M_PI / 5, SimulationObject::STATIC_PLATFORM);

			

			AddRandomDynamicObject(
				b2Vec2(-RandomFloat(15, 17), bottomPlatformHeight + 2),
				b2Vec2(RandomFloat(20, 40), 0.0f),
				0b100,
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
