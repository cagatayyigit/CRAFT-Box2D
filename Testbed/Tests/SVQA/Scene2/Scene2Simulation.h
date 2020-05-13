#pragma once

#include "Scene2Settings.h"
#include "SimulationBase.h"
#include "Box2D/Extension/b2VisBody.hpp"
#include "Box2D/Extension/b2VisPolygonShape.hpp"
#include <math.h> 

namespace svqa {
	class Scene2Simulation : public SimulationBase
	{
	public:
		typedef std::shared_ptr<Scene2Simulation> Ptr;
		Scene2Simulation(Scene2Settings::Ptr settings) : SimulationBase(settings)
		{
			m_nNumberOfObjects = settings->numberOfObjects;
			m_nNumberOfObstacles = settings->numberOfObstacles;

			SET_FILE_OUTPUT_TRUE(m_pSettings->outputVideoPath)
		}

		virtual SimulationID getIdentifier() override
		{
			return SimulationID::ID_Scene2;
		}

		void InitializeScene() override {

			


			// ------- Stack --------

			// bottom left - mid - right
			AddDynamicObject(b2Vec2(3.0f, 20.0f),b2Vec2(0.0f, 0.0f),SimulationObject::Shape::CUBE,SimulationObject::Color::RED,SimulationObject::Size::SMALL);
			AddDynamicObject(b2Vec2(5.2f, 20.0f),b2Vec2(0.0f, 0.0f),SimulationObject::Shape::CUBE,SimulationObject::Color::PURPLE,SimulationObject::Size::SMALL);
			AddDynamicObject(b2Vec2(7.4f, 20.0f),b2Vec2(0.0f, 0.0f),SimulationObject::Shape::CUBE,SimulationObject::Color::BLUE,SimulationObject::Size::SMALL);
			// middle left - right
			AddDynamicObject(b2Vec2(4.0f, 22.0f), b2Vec2(0.0f, 0.0f), SimulationObject::Shape::CUBE, SimulationObject::Color::CYAN, SimulationObject::Size::SMALL);
			AddDynamicObject(b2Vec2(6.2f, 22.0f), b2Vec2(0.0f, 0.0f), SimulationObject::Shape::CUBE, SimulationObject::Color::YELLOW, SimulationObject::Size::SMALL);
			// top
			AddDynamicObject(b2Vec2(5.0f, 24.0f), b2Vec2(0.0f, 0.0f), SimulationObject::Shape::CUBE, SimulationObject::Color::GREEN, SimulationObject::Size::SMALL);




			// ------- Top Right Platform and Circle -------
			AddStaticObject(b2Vec2(17.0f, 19.0f), 0, SimulationObject::STATIC_PLATFORM);
			AddStaticObject(b2Vec2(9.0f, 19.0f), 0, SimulationObject::STATIC_PLATFORM);
			AddStaticObject(b2Vec2(11.0f, 19.0f), 0, SimulationObject::STATIC_RAMP);

			float32 tr_circle_velocities[5] = { -34.0f, -28.0f, -20.0f, -17.0f, -14.0f };
			
			AddDynamicObject(
				b2Vec2(22.0f, 20.0f),
				b2Vec2(tr_circle_velocities[(int)RandomFloatFromHardware(0.0, 5.0)], 0.0f),
				SimulationObject::Shape::CIRCLE,
				SimulationObject::Color::PURPLE,
				SimulationObject::Size::LARGE
			);


			// ------- Inclined Platform and Rolling Circle -------
			AddStaticObject(b2Vec2(-26.5f, 12.0f), 6* M_PI / 7, SimulationObject::STATIC_PLATFORM);
			float32 rolling_circle_heights[] = { 29.0f, 18.0f, 25.0f, 40.0f, 15.0f };

			AddDynamicObject(
				b2Vec2(-22.0f, rolling_circle_heights[(int)RandomFloatFromHardware(0.0, 5.0)]),
				b2Vec2(0.0f, 0.0f),
				SimulationObject::Shape::CIRCLE,
				SimulationObject::Color::CYAN,
				SimulationObject::Size::LARGE
			);



			// ------- Bottom Left Platform and Circle -------
			AddStaticObject(b2Vec2(-7.5f, 6.0f), 0, SimulationObject::STATIC_PLATFORM);

			AddDynamicObject(
				b2Vec2(-9.0f, 8.0f),
				b2Vec2(0.0f, 0.0f),
				SimulationObject::Shape::CIRCLE,
				SimulationObject::Color::RED,
				SimulationObject::Size::LARGE
			);




			// Basket
			AddTargetBasket(b2Vec2(4.5f, -0.90f), 0.0f);



			
			// ------- Bottom Right Platform and Circle -------
			AddStaticObject(b2Vec2(17.0f, 6.0f), 0, SimulationObject::STATIC_PLATFORM);
			AddStaticObject(b2Vec2(11.0f, 6.0f), 0, SimulationObject::STATIC_RAMP);

			float32 br_circle_velocities[] = { -29.0f, -28.0f,-25.0f, -20.0f, -15.0f};

			AddDynamicObject(
				b2Vec2(22.0f, 8.0f),
				b2Vec2(br_circle_velocities[(int)RandomFloatFromHardware(0.0, 5.0)], 0.0f),
				SimulationObject::Shape::CIRCLE,
				SimulationObject::Color::GREEN,
				SimulationObject::Size::LARGE
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
