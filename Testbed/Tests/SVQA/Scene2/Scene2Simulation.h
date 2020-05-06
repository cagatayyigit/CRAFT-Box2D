#pragma once


#include "SimulationBase.h"
#include "Box2D/Extension/b2VisBody.hpp"
#include "Box2D/Extension/b2VisPolygonShape.hpp"
#include <math.h> 
#include "Scene2Settings.h"

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
			// Setup static objects.


            
            // Bottom Left  Floor
            AddStaticObject(b2Vec2(-16.0f, 6.0f), 0, SimulationObject::STATIC_PLATFORM);
			// Basket
			AddTargetBasket(b2Vec2(0.0f, 0.30f), 0.0f);


 
			// Circles

			// Stationary Bottom-Left
			float32 leftBottomCircleCoorX = (RandomFloatFromHardware(-15.0, -10.0));
			AddRandomDynamicObject(
				b2Vec2(-10.0f, 11.0f),
				b2Vec2(0.0f, 0.0f)
			);




			// Falling Circle from right
			AddRandomDynamicObject(
				b2Vec2(16.0f, 30.0f),
				b2Vec2(-21.0f, -5.0f)
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
