#pragma once

#include "Scene1Settings.h"
#include "SimulationBase.h"
#include "Box2D/Extension/b2VisBody.hpp"
#include "Box2D/Extension/b2VisPolygonShape.hpp"
#include <math.h> 

namespace svqa {
	class Scene1Simulation : public SimulationBase
	{
	public:
		typedef std::shared_ptr<Scene1Simulation> Ptr;
		Scene1Simulation(Scene1Settings::Ptr settings) : SimulationBase(settings)
		{
			m_nNumberOfObjects = settings->numberOfObjects;
			m_nNumberOfObstacles = settings->numberOfObstacles;

			SET_FILE_OUTPUT_TRUE(m_pSettings->outputVideoPath)
		}

		virtual SimulationID getIdentifier() override
		{
			return SimulationID::ID_Scene1;
		}

		void InitializeScene() override {  
			// Setup static objects.

			b2Vec2 rampPosition = b2Vec2(RandomFloatFromHardware(-36.5f, -33.5f), 4.0f);

			float32 min_angle1 = M_PI / 7.0f;
			float32 max_angle1 = M_PI / 2.0f - min_angle1;
			float32 min_angle2 = M_PI / 2.0f + min_angle1;
			float32 max_angle2 = M_PI / 2.0f + max_angle1;
			std::vector<float32> mins = std::vector<float32>();
			mins.push_back(min_angle1);
			mins.push_back(min_angle2);
			std::vector<float32> maxs = std::vector<float32>();
			maxs.push_back(max_angle1);
			maxs.push_back(max_angle2);

			float32 angle = RandomFloatWithinRanges(mins, maxs);

			float32 leftFloorLen = (RandomFloatFromHardware(15.0, 18.0));
			float32 rightFloorCoorX = (RandomFloatFromHardware(40.0, 46.0));

			

			float32 inclinedFloorLen = (RandomFloatFromHardware(9.0, 12.0));
			float32 circleV = (RandomFloatFromHardware(-5.0, -15.0));

            
            // Bottom Left  Floor
            AddStaticObject(b2Vec2(-16.0f, 6.0f), 0, SimulationObject::STATIC_PLATFORM);
			// Basket
			addTargetBasket(b2Vec2(0.0f, 0.0f), 0.0f);
            // Bottom Right Floor
            AddStaticObject(b2Vec2(16.0f, 6.0f), 0, SimulationObject::STATIC_PLATFORM);
            

			// Bottom Left  Vertical Floor
			AddStaticObject(b2Vec2(-25.0f, 16.0f), 4 * M_PI / 5, SimulationObject::STATIC_PLATFORM);


			// Middle Left  Floor
			AddStaticObject(b2Vec2(-5.0f, 18.0f), 51 * M_PI / 55, SimulationObject::STATIC_PLATFORM);
			// Middle Right Floor
			AddStaticObject(b2Vec2(16.0f, 23.0f), 0, SimulationObject::STATIC_PLATFORM);


			// Top Left  Floor
			AddStaticObject(b2Vec2(-10.0f, 35.0f), 51 * M_PI / 55, SimulationObject::STATIC_PLATFORM);

			// Ramp
			//AddStaticObject(b2Vec2(25.0f, 10.0f), 0, SimulationObject::STATIC_RAMP);


            // Inclined Floor
            //AddStaticObject(b2Vec2(-28.0f, 35.0f), angle, SimulationObject::STATIC_PLATFORM);

			// Inclined Floor
            //AddStaticObject(b2Vec2(-10.0f, 25.0f), angle, SimulationObject::STATIC_PLATFORM);

            
			
            //AddStaticObject(rampPosition, 0.0f, SimulationObject::STATIC_RAMP);
 
			// Circles

			// Stationary Bottom-Left
			float32 leftBottomCircleCoorX = (RandomFloatFromHardware(-15.0, -10.0));
			AddDynamicObject(
				b2Vec2(-10.0f, 8.0f),
				b2Vec2(0.0f, 0.0f),
				SimulationObject::CIRCLE,
				SimulationObject::GRAY,
                SimulationObject::SMALL
			);

			// Stationary Bottom-Right
			float32 rightBottomCircleCoorX = (RandomFloatFromHardware(10.0, 15.0));
			AddDynamicObject(
				b2Vec2(rightBottomCircleCoorX, 8.0f),
				b2Vec2(0.0f, 0.0f),
                SimulationObject::CIRCLE,
                SimulationObject::RED,
                SimulationObject::SMALL
			);


			



			// Moving on the Right Floor
			AddDynamicObject(
				b2Vec2(32.0f, 17.0f),
				b2Vec2(-10.0f, -4.0f),
                SimulationObject::CIRCLE,
                SimulationObject::BLUE,
                SimulationObject::SMALL
			);

			// Falling Circle from mid
			AddRandomDynamicObject(
				b2Vec2(-10.0f, 42.0f),
				b2Vec2(3.0f, -8.0f)
			);

			// Falling Circle from right
			AddRandomDynamicObject(
				b2Vec2(16.0f, 30.0f),
				b2Vec2(-21.0f, -5.0f)
			);
			

			// Falling Circle from left
			AddRandomDynamicObject(
				b2Vec2(-25.0f, 42.0f),
				b2Vec2(0.0f, -10.0f)
			);

			AddRandomDynamicObject(
				b2Vec2(-30.0f, 22.0f),
				b2Vec2(0.0f, -10.0f)
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
