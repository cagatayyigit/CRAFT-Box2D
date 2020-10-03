#pragma once

#include "Scene9Settings.h"
#include "SimulationBase.h"
#include "Box2D/Extension/b2VisBody.hpp"
#include "Box2D/Extension/b2VisPolygonShape.hpp"
#include <math.h> 

namespace svqa {
	class Scene9Simulation : public SimulationBase
	{
	public:
		typedef std::shared_ptr<Scene9Simulation> Ptr;
		Scene9Simulation(Scene9Settings::Ptr settings) : SimulationBase(settings)
		{
            m_bIncludeDynamicObjects  = settings->includeDynamicObjects;
            m_nMin_mean_max_random = settings->min_mean_max_random;

			SET_FILE_OUTPUT_TRUE(m_pSettings->outputVideoPath)
		}

		virtual SimulationID getIdentifier() override
		{
			return SimulationID::ID_Scene9;
		}

		void InitializeScene() override {
            
            std::string  c = m_nMin_mean_max_random;
            bool includeDynamicObjects = m_bIncludeDynamicObjects;
            
            
			// Basket
			AddTargetBasket(b2Vec2(getExtremeCases(c,-1, 1), -1.2f), 0.0f);


			// Top Platform
			float topPlatformHeight = getExtremeCases(c,28.0f, 31.0f);
			AddStaticObject(b2Vec2(7.0f, topPlatformHeight), M_PI, SimulationObject::STATIC_PLATFORM);
			AddStaticObject(b2Vec2(-7.0f, topPlatformHeight), M_PI, SimulationObject::STATIC_PLATFORM);
			
            
            
            AddStaticObject(b2Vec2(-getExtremeCases(c,16, 18), getExtremeCases(c,24, 25)), getExtremeCases(c,7.5f, 8.5f) * M_PI / 9.0f, SimulationObject::STATIC_PLATFORM);
            AddStaticObject(b2Vec2(getExtremeCases(c,16, 18), getExtremeCases(c,24, 25)), -getExtremeCases(c,7.5f, 8.5f) * M_PI / 9.0f, SimulationObject::STATIC_PLATFORM);


            // Middle Platform
            float middlePlatformHeight = getExtremeCases(c,14, 16);
            AddStaticObject(b2Vec2(getExtremeCases(c,4.5, 5.5), middlePlatformHeight), M_PI, SimulationObject::STATIC_PLATFORM);
            AddStaticObject(b2Vec2(-getExtremeCases(c,4.5, 5.5), middlePlatformHeight), M_PI, SimulationObject::STATIC_PLATFORM);

            
            AddStaticObject(b2Vec2(-getExtremeCases(c,12, 14), getExtremeCases(c,5, 6.5f)), getExtremeCases(c,7.5f, 8.25f) * M_PI / 9.0f, SimulationObject::STATIC_PLATFORM);
            AddStaticObject(b2Vec2(getExtremeCases(c,12, 14), getExtremeCases(c,5, 6.5f)), -getExtremeCases(c,7.5f, 8.25f) * M_PI / 9.0f, SimulationObject::STATIC_PLATFORM);
            
            
            if (includeDynamicObjects) {
                // Objects at top.
                AddRandomDynamicObject(
                    b2Vec2(getExtremeCases(c,1.5f, 12.5f), topPlatformHeight + 1.5f),
                    b2Vec2(getExtremeCases(c,40.0f, 20.0f), 0.0f),
                    0b100,
                    SimulationObject::CIRCLE
                );
                AddRandomDynamicObject(
                    b2Vec2(-getExtremeCases(c,1.5f, 12.5f), topPlatformHeight + 1.5f),
                    b2Vec2(-getExtremeCases(c,40.0f, 20.0f), 0.0f),
                    0b100,
                    SimulationObject::CIRCLE
                );
        
                // Middle objects.
                AddRandomDynamicObject(
                    b2Vec2(-getExtremeCases(c,8.0f, 12.0f), middlePlatformHeight + 1.5f),
                    b2Vec2(0.0f, 0.0f)
                );
                AddRandomDynamicObject(
                    b2Vec2(getExtremeCases(c,8.0f, 12.0f), middlePlatformHeight + 1.5f),
                    b2Vec2(0.0f, 0.0f)
                );
            }

		}

	private:
        bool m_bIncludeDynamicObjects;
        std::string  m_nMin_mean_max_random;
        
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
