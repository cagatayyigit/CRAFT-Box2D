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
			AddTargetBasket(b2Vec2(8.0f, -1.2f), 0.0f);




			//left
			AddStaticObject(b2Vec2(-12.0f, 28.0f), 5*  M_PI  / 6, SimulationObject::STATIC_PLATFORM);

			AddDynamicObject(
				b2Vec2(-12.0f, 31.0f),
				b2Vec2(0.0f, -15.0f),
				SimulationObject::CIRCLE,
				SimulationObject::CYAN,
				SimulationObject::LARGE
			);

			
			//right

			AddStaticObject(b2Vec2(16.0f, 14.0f), - 15 * M_PI / 16, SimulationObject::STATIC_PLATFORM);

			
			// mid
			AddStaticObject(b2Vec2(5.0f, 19.0f), M_PI, SimulationObject::STATIC_PLATFORM);
			AddDynamicObject(
				b2Vec2(4.0f, 21.0f),
				b2Vec2(-8.0f, 0.0f),
				SimulationObject::CIRCLE,
				SimulationObject::GREEN,
				SimulationObject::LARGE
			);


			// bottom
			AddStaticObject(b2Vec2(-5.0f, 7.0f),  M_PI , SimulationObject::STATIC_PLATFORM);
			AddStaticObject(b2Vec2(-19.0f, 7.0f),  M_PI , SimulationObject::STATIC_PLATFORM);
			AddDynamicObject(
				b2Vec2(-17.0f, 9.0f),
				b2Vec2(3.0f, 0.0f),
				SimulationObject::CIRCLE,
				SimulationObject::RED,
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
