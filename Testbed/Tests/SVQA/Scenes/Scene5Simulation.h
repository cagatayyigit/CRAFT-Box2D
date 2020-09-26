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
            m_bIncludeDynamicObjects  = settings->includeDynamicObjects;
            m_nMin_mean_max_random = settings->min_mean_max_random;

			SET_FILE_OUTPUT_TRUE(m_pSettings->outputVideoPath)
		}

		virtual SimulationID getIdentifier() override
		{
			return SimulationID::ID_Scene4;
		}

		void InitializeScene() override {
            
            std::string  c = m_nMin_mean_max_random;
            bool includeDynamicObjects = m_bIncludeDynamicObjects;
            
            
			// Basket
			AddTargetBasket(b2Vec2(getExtremeCases(c,-5.0f, 5.0f), -1.2f), 0.0f);

            
            AddStaticObject(b2Vec2(getExtremeCases(c,-9.0f, -5.0f), 11.0f), M_PI_2 , SimulationObject::STATIC_RAMP);
            AddStaticObject(b2Vec2(-11.0f, 11.0f), 0, SimulationObject::STATIC_PLATFORM);
            AddStaticObject(b2Vec2(-18.0f, 11.0f), 0, SimulationObject::STATIC_PLATFORM);
            
            AddStaticObject(b2Vec2(getExtremeCases(c,8.0f, 13.0f), 21.0f), 30 * M_PI / getExtremeCases(c,31.0f, 35.0f), SimulationObject::STATIC_PLATFORM);
            AddStaticObject(b2Vec2(16.0f, 6.0f), - 15 * M_PI / getExtremeCases(c,16.0f, 19.0f), SimulationObject::STATIC_PLATFORM);
            AddStaticObject(b2Vec2(12.0f, 14.0f), 0, SimulationObject::STATIC_PLATFORM);
            
            
            if(includeDynamicObjects){
                
                AddRandomDynamicObject(
                    b2Vec2(getExtremeCases(c,-20.0f, -18.0f), 13.5f),
                    b2Vec2(getExtremeCases(c,30.0f, 39.0f), 0.0f),
                    0b100,
                    SimulationObject::CIRCLE
                    );
                
                AddRandomDynamicObject(b2Vec2(12.0f, 23.0f), b2Vec2(0.0f, 0.0f));
                AddRandomDynamicObject(b2Vec2(12.0f, 16.0f), b2Vec2(0.0f, 0.0f));
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
