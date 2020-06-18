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

			std::vector<SimulationObject::Color> distinc_colors;
			while(distinc_colors.size() < 5) {
				SimulationObject::Color c = SimulationObject::getRandomColor();
				if (std::find(distinc_colors.begin(), distinc_colors.end(), c) == distinc_colors.end()) {
					distinc_colors.push_back(c);
				}
			}
			
			// Basket
			AddTargetBasket(b2Vec2(20.5f, 19.0f), 0.0f);



			AddStaticObject(b2Vec2(7.0f, 29.5f), M_PI, SimulationObject::STATIC_PLATFORM);
			AddStaticObject(b2Vec2(-3.0f, 29.5f), M_PI, SimulationObject::STATIC_PLATFORM);
			AddDynamicObject(
				b2Vec2(12.0f, 32.0f),
				b2Vec2(-70.9f, 0.0f),
				SimulationObject::CIRCLE,
				SimulationObject::RED,
				SimulationObject::LARGE
			);



			// top
			AddStaticObject(b2Vec2(-17.0f, 22.5f), M_PI, SimulationObject::STATIC_PLATFORM);
			AddStaticObject(b2Vec2(-7.0f, 22.5f), M_PI, SimulationObject::STATIC_PLATFORM);
		


			// mid
			AddStaticObject(b2Vec2(-17.0f, 15.5f), M_PI, SimulationObject::STATIC_PLATFORM);
			/*AddDynamicObject(
				b2Vec2(-18.0f, 18.0f),
				b2Vec2(22.9f, 0.0f),
				SimulationObject::CIRCLE,
				SimulationObject::GREEN,
				SimulationObject::LARGE
			);*/

	
			
			// bottom
			AddStaticObject(b2Vec2(-17.0f, 8.5f), M_PI, SimulationObject::STATIC_PLATFORM);
			AddStaticObject(b2Vec2(-2.8f, 13.0f), - 4 * M_PI / 5, SimulationObject::STATIC_PLATFORM);
			AddStaticObject(b2Vec2(3.3f, 16.1f), -4 * M_PI / 5, SimulationObject::STATIC_PLATFORM);
			AddStaticObject(b2Vec2(9.3f, 19.06f), -4 * M_PI / 5, SimulationObject::STATIC_PLATFORM);

			

			AddDynamicObject(
				b2Vec2(-12.0f, 11.0f),
				b2Vec2(28.0f, 0.0f),
				SimulationObject::CIRCLE,
				SimulationObject::CYAN,
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
