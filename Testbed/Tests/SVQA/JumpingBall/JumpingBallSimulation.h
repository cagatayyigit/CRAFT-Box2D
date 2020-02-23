#pragma once

#include "SimulationColor.h"
#include "JumpingBallSettings.h"
#include "SimulationBase.h"
#include "Box2D/Extension/b2VisBody.hpp"
#include "Box2D/Extension/b2VisPolygonShape.hpp"
#include <math.h> 

namespace svqa {
	class JumpingBallSimulation : public SimulationBase
	{
	public:
		typedef std::shared_ptr<JumpingBallSimulation> Ptr;

		JumpingBallSimulation(JumpingBallSettings::Ptr settings) : SimulationBase(settings)
		{
			m_nNumberOfObjects = 1;
			SET_FILE_OUTPUT_TRUE(m_pSettings->outputFilePath)
		}

		// Our "game loop".
		virtual void Step(SettingsBase* settings) override
		{
			const bool stable = isSceneStable();
			const bool addObject = stable && m_nNumberOfObjects > 0;

			if (addObject) {

				addStaticObject(b2Vec2(30, 40), M_PI / 16,
					std::make_shared<b2PolygonShape>(SimulationObject::getRectangle(35.0f, 0.5f)), SimulationObject::CUSTOM_RECTANGLE,
					SimulationMaterial::METAL, SimulationColor::RED);

				addStaticObject(b2Vec2(-20.0f, 28.0f), 0,
					std::make_shared<b2PolygonShape>(SimulationObject::getRectangle(4.0f, 1.0f)), SimulationObject::CUSTOM_RECTANGLE,
					SimulationMaterial::METAL, SimulationColor::GRAY);

				addStaticObject(b2Vec2(0, 22), -1 * M_PI / 16,
					std::make_shared<b2PolygonShape>(SimulationObject::getRectangle(16.0f, 0.5f)), SimulationObject::CUSTOM_RECTANGLE,
					SimulationMaterial::METAL, SimulationColor::RED);

				addStaticObject(b2Vec2(40, 0), M_PI / 4,
					std::make_shared<b2PolygonShape>(SimulationObject::getRectangle(10.0f, 0.5f)), SimulationObject::CUSTOM_RECTANGLE,
					SimulationMaterial::METAL, SimulationColor::GRAY);


				addStaticObject(b2Vec2(-20.0f, 28.0f), 0,
					std::make_shared<b2PolygonShape>(SimulationObject::getRectangle(4.0f, 1.0f)), SimulationObject::CUSTOM_RECTANGLE,
					SimulationMaterial::METAL, SimulationColor::GRAY);

				addStaticObject(b2Vec2(28.0f, 8.0f), 0,
					std::make_shared<b2PolygonShape>(SimulationObject::getRectangle(4.0f, 1.0f)), SimulationObject::CUSTOM_RECTANGLE,
					SimulationMaterial::METAL, SimulationColor::GRAY);



				// statics
				addStaticObject(b2Vec2(-30, -3), M_PI, SimulationObject::BIG_TRIANGLE, SimulationMaterial::METAL, SimulationColor::PURPLE);
				addStaticObject(b2Vec2(-19, -5), M_PI, SimulationObject::BIG_TRIANGLE, SimulationMaterial::METAL, SimulationColor::PURPLE);

				addStaticObject(b2Vec2(-20.0f, 28.0f), 0,
					std::make_shared<b2PolygonShape>(SimulationObject::getRectangle(4.0f, 1.0f)), SimulationObject::CUSTOM_RECTANGLE,
					SimulationMaterial::METAL, SimulationColor::GRAY);

				addStaticObject(b2Vec2(28.0f, 8.0f), 0,
					std::make_shared<b2PolygonShape>(SimulationObject::getRectangle(4.0f, 1.0f)), SimulationObject::CUSTOM_RECTANGLE,
					SimulationMaterial::METAL, SimulationColor::GRAY);





				// rod
				addDynamicObject(b2Vec2(-32, 0.5f), b2Vec2(0, 0), SimulationObject::ROD_RECTANGLE, SimulationMaterial::RUBBER, SimulationColor::TYPE::CYAN);

				// circles
				addDynamicObject(b2Vec2(-25, 4), b2Vec2(0.0f, 0.0f), SimulationObject::SMALL_CIRCLE, SimulationMaterial::RUBBER, SimulationColor::TYPE::PURPLE);
				addDynamicObject(b2Vec2(-23.0f, 35.0f), b2Vec2(0.0f, 0.0f), SimulationObject::BIG_CIRCLE, SimulationMaterial::METAL, SimulationColor::TYPE::BLUE);
				addDynamicObject(b2Vec2(30, 45), b2Vec2(-20.0f, -12.0f), SimulationObject::SMALL_CIRCLE, SimulationMaterial::RUBBER, SimulationColor::TYPE::GREEN);
				addDynamicObject(b2Vec2(29, 10), b2Vec2(0.0f, 0.0f), SimulationObject::SMALL_CIRCLE, SimulationMaterial::RUBBER, SimulationColor::TYPE::PURPLE);


				// stack
				addDynamicObject(b2Vec2(5.0f, -4.0f), b2Vec2(0.0f, 0.0f), SimulationObject::BIG_CUBE, SimulationMaterial::RUBBER, SimulationColor::TYPE::BLUE);
				addDynamicObject(b2Vec2(4.8f, -2.0f), b2Vec2(0.0f, 0.0f), SimulationObject::BIG_CUBE, SimulationMaterial::RUBBER, SimulationColor::TYPE::BLUE);
				addDynamicObject(b2Vec2(5.2f, 0.0f), b2Vec2(0.0f, 0.0f), SimulationObject::BIG_CUBE, SimulationMaterial::RUBBER, SimulationColor::TYPE::BLUE);
				addDynamicObject(b2Vec2(4.8f, 2.0f), b2Vec2(0.0f, 0.0f), SimulationObject::BIG_CUBE, SimulationMaterial::RUBBER, SimulationColor::TYPE::BLUE);
				addDynamicObject(b2Vec2(5.2f, 4.0f), b2Vec2(0.0f, 0.0f), SimulationObject::BIG_CUBE, SimulationMaterial::RUBBER, SimulationColor::TYPE::BLUE);
				addDynamicObject(b2Vec2(4.8f, 6.0f), b2Vec2(0.0f, 0.0f), SimulationObject::BIG_CUBE, SimulationMaterial::RUBBER, SimulationColor::TYPE::BLUE);
				addDynamicObject(b2Vec2(5.2f, 8.0f), b2Vec2(0.0f, 0.0f), SimulationObject::BIG_CUBE, SimulationMaterial::RUBBER, SimulationColor::TYPE::BLUE);
				addDynamicObject(b2Vec2(4.8f, 10.0f), b2Vec2(0.0f, 0.0f), SimulationObject::BIG_CUBE, SimulationMaterial::RUBBER, SimulationColor::TYPE::BLUE);
				addDynamicObject(b2Vec2(5.2f, 12.0f), b2Vec2(0.0f, 0.0f), SimulationObject::BIG_CUBE, SimulationMaterial::RUBBER, SimulationColor::TYPE::BLUE);
				addDynamicObject(b2Vec2(4.8f, 14.0f), b2Vec2(0.0f, 0.0f), SimulationObject::BIG_CUBE, SimulationMaterial::RUBBER, SimulationColor::TYPE::BLUE);
				addDynamicObject(b2Vec2(5.2f, 16.0f), b2Vec2(0.0f, 0.0f), SimulationObject::BIG_CUBE, SimulationMaterial::RUBBER, SimulationColor::TYPE::BLUE);
				m_nNumberOfObjects--;
			}

            SimulationBase::Step(settings);
		}

		virtual SimulationID getIdentifier() override
		{
			return SimulationID::ID_ObstructedPath;
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
