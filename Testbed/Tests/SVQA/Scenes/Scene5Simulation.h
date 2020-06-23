#pragma once

#include "Scene5Settings.h"
#include "SimulationBase.h"
#include "Box2D/Extension/b2VisBody.hpp"
#include "Box2D/Extension/b2VisPolygonShape.hpp"
#include <math.h> 

namespace svqa {
	class Scene5Simulation : public SimulationBase
	{
	public:
		typedef std::shared_ptr<Scene5Simulation> Ptr;
		Scene5Simulation(Scene5Settings::Ptr settings) : SimulationBase(settings)
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

			std::vector<SimulationObject::Color> distinc_colors;
			while(distinc_colors.size() < 5) {
				SimulationObject::Color c = SimulationObject::getRandomColor();
				if (std::find(distinc_colors.begin(), distinc_colors.end(), c) == distinc_colors.end()) {
					distinc_colors.push_back(c);
				}
			}
			
			// Basket
			AddTargetBasket(b2Vec2(0.0f, -1.2f), 0.0f);

			


			AddDynamicObject(
				b2Vec2(-24.0f, 11.5f),
				b2Vec2(29.0f, 0.0f),  // 38.0f 29.0f
				SimulationObject::Shape::CIRCLE,
				distinc_colors[0],
				SimulationObject::getRandomSize());

			//AddStaticObject(b2Vec2(-27.0f, 16.0f), 6 * M_PI / 7, SimulationObject::STATIC_PLATFORM);
			AddStaticObject(b2Vec2(-6.0f, 11.0f), M_PI_2 , SimulationObject::STATIC_RAMP);
			AddStaticObject(b2Vec2(-11.0f, 11.0f), 0, SimulationObject::STATIC_PLATFORM);
			AddStaticObject(b2Vec2(-18.0f, 11.0f), 0, SimulationObject::STATIC_PLATFORM);



			AddRandomDynamicObject(b2Vec2(12.0f, 24.0f), b2Vec2(0.0f, 0.0f));
			AddStaticObject(b2Vec2(12.0f, 22.0f), 30 * M_PI / 32, SimulationObject::STATIC_PLATFORM);



			AddRandomDynamicObject(b2Vec2(12.0f, 16.0f), b2Vec2(0.0f, 0.0f));
			AddStaticObject(b2Vec2(12.0f, 14.0f), 0, SimulationObject::STATIC_PLATFORM);


			


			AddStaticObject(b2Vec2(15.0f, 5.0f), - 15 * M_PI / 16, SimulationObject::STATIC_PLATFORM);

			

			
			



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
