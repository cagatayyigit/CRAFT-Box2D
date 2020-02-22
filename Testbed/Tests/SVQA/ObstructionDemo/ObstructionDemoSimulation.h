#pragma once

#include "SimulationColor.h"
#include "ObstructionDemoSettings.h"
#include "SimulationBase.h"
#include "Box2D/Extension/b2VisBody.hpp"
#include "Box2D/Extension/b2VisPolygonShape.hpp"
#include <math.h>

namespace svqa {
	class ObstructionDemoSimulation : public SimulationBase
	{
	public:
		typedef std::shared_ptr<ObstructionDemoSimulation> Ptr;

		ObstructionDemoSimulation(ObstructionDemoSettings::Ptr _settings_) : SimulationBase(_settings_)
		{
			m_nNumberOfObjects = _settings_->numberOfObjects;
			m_nNumberOfObstacles = _settings_->numberOfObstacles;

			m_fSpeed = RandomFloat(15.0f, 30.0f);

			m_vObstaclePosition = b2Vec2(RandomFloat(-10.0f, 10.0f), RandomFloat(15.0f, 40.0f));
			m_vMovingObjPosition = b2Vec2(RandomFloat(-25.0f, -10.0), 2.5f);
			m_vStagnantObjPosition = b2Vec2(RandomFloat(10.0f, 30.0f), 2.5f);

			m_vInitialDropVelocity = b2Vec2(0.0f, RandomFloat(-20.0f, -40.0f));

			SET_FILE_OUTPUT_TRUE(m_pSettings->outputFilePath)
		}

		virtual void Step(SettingsBase* settings) override
		{
			const bool stable = isSceneStable();
			setSceneInitialized(!isGeneratingFromJSON());
			const bool terminateSimulation = isSceneInitialized() && stable;

			if (!isSceneInitialized()) {
				addSimulationObject(m_vMovingObjPosition, b2Vec2(m_fSpeed, 0.0f), SimulationObject::SMALL_CIRCLE, SimulationColor::TYPE::BROWN);

				addSimulationObject(m_vObstaclePosition, m_vInitialDropVelocity, SimulationObject::BIG_CUBE, SimulationColor::TYPE::RED);

				addSimulationObject(m_vStagnantObjPosition, b2Vec2_zero, SimulationObject::SMALL_CIRCLE, SimulationColor::TYPE::BLUE);

				setSceneInitialized(true);
			}

			if (isSceneInitialized() && !m_SceneSnapshotTaken) {
				m_TakeSceneSnapshot = true;
			}

			if (terminateSimulation)
			{
				settings->terminate = true;
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


		const std::vector<SimulationObject::TYPE> m_vSimulationObjectTypes = { SimulationObject::SMALL_CUBE,
			SimulationObject::BIG_CUBE, SimulationObject::SMALL_HEXAGON, SimulationObject::BIG_HEXAGON,
			SimulationObject::SMALL_TRIANGLE, SimulationObject::BIG_TRIANGLE };

		void addSimulationObject(b2Vec2 position, b2Vec2 velocity, SimulationObject::TYPE objType, SimulationColor color)
		{
			SimulationObject object = SimulationObject(objType);

			ShapePtr shape = object.getShape();

			SimulationMaterial mat = SimulationMaterial(SimulationMaterial::RUBBER);

			b2BodyDef bd;
			bd.type = b2_dynamicBody;
			bd.position = position;
			bd.angle = RandomFloat(0.0f, M_PI);
			bd.linearVelocity = velocity;
			BODY* body = (BODY*)m_world->CreateBody(&bd);
			body->CreateFixture(shape.get(), mat.getDensity());

			body->setTexture(mat.getTexture());
			body->setColor(color.GetColor());

			auto objectState = ObjectState::create(body, mat.type, color.type, object.type);
			body->SetUserData(objectState.get());

			m_SceneJSONState.add(objectState);
		}
	};
}
