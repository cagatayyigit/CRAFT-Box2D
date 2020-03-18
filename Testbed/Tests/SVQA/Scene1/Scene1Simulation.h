#pragma once

#include "SimulationColor.h"
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
			m_nNumberOfObjects = 1;
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

			float32 leftBottomCircleCoorX = (RandomFloatFromHardware(-30.0, 10.0));
			float32 rightBottomCircleCoorX = (RandomFloatFromHardware(12.0, 30.0));

			float32 inclinedFloorLen = (RandomFloatFromHardware(9.0, 12.0));
			float32 circleV = (RandomFloatFromHardware(-5.0, -15.0));


			// Left  Floor
			AddStaticObject(
				b2Vec2(-16.0f, 3.0f),
				0,
				std::make_shared<b2PolygonShape>(SimulationObject::getRectangle(leftFloorLen, 1.0f)),
				SimulationObject::CUSTOM_RECTANGLE,
				SimulationMaterial::METAL,
				SimulationColor::GRAY
			);

			// Right Floor
			AddStaticObject(
				b2Vec2(rightFloorCoorX, 3.0f),
				0,
				std::make_shared<b2PolygonShape>(SimulationObject::getRectangle(35.0f, 1.0f)),
				SimulationObject::CUSTOM_RECTANGLE,
				SimulationMaterial::METAL,
				SimulationColor::GRAY
			);


			// Inclined Floor
			AddStaticObject(
				b2Vec2(-28.0f, 35.0f),
				angle,
				std::make_shared<b2PolygonShape>(SimulationObject::getRectangle(6.0f, 0.5f)),
				SimulationObject::CUSTOM_RECTANGLE,
				SimulationMaterial::METAL,
				SimulationColor::GRAY
			);

			// Inclined Floor
			AddStaticObject(
				b2Vec2(-10.0f, 25.0f),
				M_PI / 4,
				std::make_shared<b2PolygonShape>(SimulationObject::getRectangle(inclinedFloorLen, 1.0f)),
				SimulationObject::CUSTOM_RECTANGLE,
				SimulationMaterial::METAL,
				SimulationColor::GRAY
			);

			// Big Ramp
			AddStaticObject(
				rampPosition,
				0,
				std::make_shared<b2PolygonShape>(SimulationObject::getRightTriangle(25, 20)),
				SimulationObject::BIG_TRIANGLE,
				SimulationMaterial::METAL,
				SimulationColor::PURPLE
			);

			// Small Ramp
			AddStaticObject(
				b2Vec2(-40.0f, -6.0f),
				0,
				std::make_shared<b2PolygonShape>(SimulationObject::getRightTriangle(3, 3)),
				SimulationObject::BIG_TRIANGLE,
				SimulationMaterial::METAL,
				SimulationColor::PURPLE
			);


			// Circles
			// Stationary Bottom-Left
			AddDynamicObject(
				b2Vec2(leftBottomCircleCoorX, -3.0f),
				b2Vec2(0.0f, 0.0f),
				SimulationObject::SMALL_CIRCLE,
				SimulationMaterial::RUBBER,
				SimulationColor::TYPE::GREEN
			);

			// Stationary Bottom-Right
			AddDynamicObject(
				b2Vec2(rightBottomCircleCoorX, -3.0f),
				b2Vec2(0.0f, 0.0f),
				SimulationObject::SMALL_CIRCLE,
				SimulationMaterial::RUBBER,
				SimulationColor::TYPE::RED
			);

			// Moving on the Right Floor
			AddDynamicObject(
				b2Vec2(30.0f, 6.0f),
				b2Vec2(circleV, 0.0f),
				SimulationObject::SMALL_CIRCLE,
				SimulationMaterial::RUBBER,
				SimulationColor::TYPE::BLUE
			);

			AddDynamicObject(
				b2Vec2(-30.0f, 42.0f),
				b2Vec2(0.0f, 0.0f),
				SimulationObject::SMALL_CIRCLE,
				SimulationMaterial::RUBBER,
				SimulationColor::TYPE::YELLOW
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
