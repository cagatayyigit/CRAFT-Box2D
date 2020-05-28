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

			std::vector<SimulationObject::Color> distinc_colors;
			while(distinc_colors.size() < 4) {
				SimulationObject::Color c = SimulationObject::getRandomColor();
				if (std::find(distinc_colors.begin(), distinc_colors.end(), c) == distinc_colors.end()) {
					distinc_colors.push_back(c);
				}
			}
			
			// Basket
			AddTargetBasket(b2Vec2(4.5f, -0.90f), 0.0f);


			


			// ------- Top Right Platform and Circle -------
			AddStaticObject(b2Vec2(17.0f, 19.0f), 0, SimulationObject::STATIC_PLATFORM);
			AddStaticObject(b2Vec2(9.0f, 19.0f), 0, SimulationObject::STATIC_PLATFORM);
			AddStaticObject(b2Vec2(11.0f, 19.0f), 0, SimulationObject::STATIC_RAMP);

			float32 tr_circle_velocities[5] = { -24.0f, -28.0f, -25.0f, -18.0f, -19.0f };
			
			AddDynamicObject(
				b2Vec2(22.0f, 20.0f),
				b2Vec2(tr_circle_velocities[(int)RandomFloatFromHardware(0.0, 5.0)], 0.0f),
				SimulationObject::Shape::CIRCLE,
				distinc_colors[0],
				SimulationObject::getRandomSize()
			);


			// ------- Inclined Platform and Rolling Circle -------
			AddStaticObject(b2Vec2(-26.5f, 12.0f), 6* M_PI / 7, SimulationObject::STATIC_PLATFORM);
			float32 rolling_circle_heights[] = { 29.0f, 18.0f, 25.0f, 40.0f, 19.0f };

			AddDynamicObject(
				b2Vec2(-22.0f, rolling_circle_heights[(int)RandomFloatFromHardware(0.0, 5.0)]),
				b2Vec2(0.0f, 0.0f),
				SimulationObject::Shape::CIRCLE,
				distinc_colors[1],
				SimulationObject::getRandomSize()
			);



			// ------- Bottom Left Platform and Circle -------
			AddStaticObject(b2Vec2(-7.5f, 6.0f), 0, SimulationObject::STATIC_PLATFORM);

			AddDynamicObject(
				b2Vec2(-9.0f, 8.0f),
				b2Vec2(0.0f, 0.0f),
				SimulationObject::Shape::CIRCLE,
				distinc_colors[2],
				SimulationObject::getRandomSize()
			);




			



			
			// ------- Bottom Right Platform and Circle -------
			AddStaticObject(b2Vec2(17.0f, 6.0f), 0, SimulationObject::STATIC_PLATFORM);
			AddStaticObject(b2Vec2(11.0f, 6.0f), 0, SimulationObject::STATIC_RAMP);

			float32 br_circle_velocities[] = { -29.0f, -28.0f,-25.0f, -20.0f, -15.0f};

			AddDynamicObject(
				b2Vec2(22.0f, 8.0f),
				b2Vec2(br_circle_velocities[(int)RandomFloatFromHardware(0.0, 5.0)], 0.0f),
				SimulationObject::Shape::CIRCLE,
				distinc_colors[3],
				SimulationObject::getRandomSize()
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
