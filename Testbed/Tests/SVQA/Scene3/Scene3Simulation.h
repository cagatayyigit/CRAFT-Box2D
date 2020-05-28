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
			AddTargetBasket(b2Vec2(21.0f, -1.2f), 0.0f);
			AddTargetBasket(b2Vec2(-21.0f, -1.2f), 0.0f);


			/*float32 tr_circle_velocities[5] = { -24.0f, -28.0f, -25.0f, -18.0f, -19.0f };
			AddDynamicObject(
				b2Vec2(22.0f, 20.0f),
				b2Vec2(tr_circle_velocities[(int)RandomFloatFromHardware(0.0, 5.0)], 0.0f),
				SimulationObject::Shape::CIRCLE,
				distinc_colors[0],
				SimulationObject::getRandomSize()
			);*/
			


			AddDynamicObject(
				b2Vec2(-18.0f, 25.2f),
				b2Vec2(0.0f, 0.0f),
				SimulationObject::Shape::CIRCLE,
				SimulationObject::getRandomColor(),
				SimulationObject::LARGE);
			// ------- Inclined Platform-------
			AddStaticObject(b2Vec2(-13.0f, 19.2f), 4 * M_PI / 5, SimulationObject::STATIC_PLATFORM);
			AddStaticObject(b2Vec2(10.0f, 19.2f), -4 * M_PI / 5, SimulationObject::STATIC_PLATFORM);

			



			AddDynamicObject(
				b2Vec2(-18.0f, 11.2f),
				b2Vec2(8.0f, 0.0f),
				SimulationObject::Shape::CIRCLE,
				SimulationObject::getRandomColor(),
				SimulationObject::LARGE);


			// ------- Top Platform-------
			//AddStaticObject(b2Vec2(-18.0f, 9.2f), 0, SimulationObject::STATIC_PLATFORM);
			AddStaticObject(b2Vec2(-12.0f, 9.2f), 0, SimulationObject::STATIC_PLATFORM);
			AddStaticObject(b2Vec2(10.5f, 9.2f), 0, SimulationObject::STATIC_PLATFORM);
		


			AddDynamicObject(
				b2Vec2(-18.0f, 5.5f),
				b2Vec2(7.0f, 0.0f),
				SimulationObject::Shape::CIRCLE,
				SimulationObject::getRandomColor(),
				SimulationObject::LARGE);



			// ------- Bottom Platform -------
			AddStaticObject(b2Vec2(-10.0f, 4.0f), 0, SimulationObject::STATIC_PLATFORM);
			AddStaticObject(b2Vec2(-2.0f, 4.0f), 0, SimulationObject::STATIC_PLATFORM);
			AddStaticObject(b2Vec2(9.5f, 4.0f), 0, SimulationObject::STATIC_PLATFORM);
			//AddStaticObject(b2Vec2(23.0f, 0.0f), 0, SimulationObject::STATIC_PLATFORM);

			
			



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
