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
        
        float getExtremeCases(int x, float min, float max){
            if (x == -1)
                    return min;
            if (x == 0)
                    return (min + max) / 2.0;
            if (x == 1)
                    return max;
            return RandomFloatFromHardware(min, max);
        }
        
		void InitializeScene() override {
            
            int c = 1;
			
			// Basket
			// make x coord. random
            float min_0 = 5.0;
            float mean_0 = 7.5;
            float max_0 = 10.0;
            float random_0 = RandomFloatFromHardware(min_0, max_0);
			AddTargetBasket(b2Vec2(getExtremeCases(c, min_0, max_0), -1.2f), 0.0f);


			//left
			// make angle random
            float min_1 = 5.5;
            float mean_1 = 6.25;
            float max_1 = 7.0;
            float random_1 = RandomFloatFromHardware(min_1, max_1);
			AddStaticObject(b2Vec2(-12.0f, 28.0f), 5*  M_PI  / getExtremeCases(c, min_1, max_1), SimulationObject::STATIC_PLATFORM);

          
			// make y-coord random
			AddRandomDynamicObject(
				b2Vec2(-12.0f, 31.0f),
				b2Vec2(0.0f, -15.0f)
			);
       
			
			//right
			// make angle random
            float min_2 = 16.0;
            float mean_2 = 17.5;
            float max_2 = 19.0;
            float random_2 = RandomFloatFromHardware(min_2 , max_2);
			AddStaticObject(b2Vec2(16.0f, 14.0f), - 15 * M_PI / getExtremeCases(c, min_2, max_2), SimulationObject::STATIC_PLATFORM);

			
			// mid
			// make y-coord random
            float min_3 = 17.0;
            float mean_3 = 18.5;
            float max_3 = 20.0;
			float random_3 = RandomFloatFromHardware(min_3, max_3);
			AddStaticObject(b2Vec2(5.0f, getExtremeCases(c, min_3, max_3)), M_PI, SimulationObject::STATIC_PLATFORM);

          
			// make x coord. random
			// make Velocity random
			AddRandomDynamicObject(
				b2Vec2(4.0f, random_3 + 2.0f),
				b2Vec2(-8.0f, 0.0f),
				0b100,
				SimulationObject::CIRCLE
			);
            

			// bottom
            float min_4 = 3.0;
            float mean_4 = 6.0;
            float max_4 = 9.0;
            float random_4 = RandomFloatFromHardware(min_4, max_4);
			AddStaticObject(b2Vec2(-5.0f,  getExtremeCases(c, min_4, max_4)),  M_PI , SimulationObject::STATIC_PLATFORM);
			AddStaticObject(b2Vec2(-19.0f, getExtremeCases(c, min_4, max_4)),  M_PI , SimulationObject::STATIC_PLATFORM);

     
			AddRandomDynamicObject(
				b2Vec2(RandomFloatFromHardware(-20.0, -16.0), random_4 + 2.0f),  // make x coord. random
				b2Vec2(RandomFloatFromHardware(8.0, 3.0), 0.0f),     // make x-velocity random
				0b100,
				SimulationObject::CIRCLE
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
