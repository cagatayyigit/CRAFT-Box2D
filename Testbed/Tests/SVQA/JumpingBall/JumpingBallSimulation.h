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

				createBoundaries(40.0f, 50.0f, 5.0f);
		}

		// Our "game loop".
		virtual void Step(SettingsBase* settings) override
		{
			const bool stable = isSceneStable();
			const bool addObject = stable && m_nNumberOfObjects > 0;
			const bool terminateSimulation = m_nNumberOfObjects == 0 && stable;

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
				addDynamicObject(b2Vec2(5.0f, -4.0f), b2Vec2(0.0f, 0.0f), SimulationObject::SQUARE, SimulationMaterial::RUBBER, SimulationColor::TYPE::BLUE);
				addDynamicObject(b2Vec2(4.8f, -2.0f), b2Vec2(0.0f, 0.0f), SimulationObject::SQUARE, SimulationMaterial::RUBBER, SimulationColor::TYPE::BLUE);
				addDynamicObject(b2Vec2(5.2f, 0.0f), b2Vec2(0.0f, 0.0f), SimulationObject::SQUARE, SimulationMaterial::RUBBER, SimulationColor::TYPE::BLUE);
				addDynamicObject(b2Vec2(4.8f, 2.0f), b2Vec2(0.0f, 0.0f), SimulationObject::SQUARE, SimulationMaterial::RUBBER, SimulationColor::TYPE::BLUE);
				addDynamicObject(b2Vec2(5.2f, 4.0f), b2Vec2(0.0f, 0.0f), SimulationObject::SQUARE, SimulationMaterial::RUBBER, SimulationColor::TYPE::BLUE);
				addDynamicObject(b2Vec2(4.8f, 6.0f), b2Vec2(0.0f, 0.0f), SimulationObject::SQUARE, SimulationMaterial::RUBBER, SimulationColor::TYPE::BLUE);
				addDynamicObject(b2Vec2(5.2f, 8.0f), b2Vec2(0.0f, 0.0f), SimulationObject::SQUARE, SimulationMaterial::RUBBER, SimulationColor::TYPE::BLUE);
				addDynamicObject(b2Vec2(4.8f, 10.0f), b2Vec2(0.0f, 0.0f), SimulationObject::SQUARE, SimulationMaterial::RUBBER, SimulationColor::TYPE::BLUE);
				addDynamicObject(b2Vec2(5.2f, 12.0f), b2Vec2(0.0f, 0.0f), SimulationObject::SQUARE, SimulationMaterial::RUBBER, SimulationColor::TYPE::BLUE);
				addDynamicObject(b2Vec2(4.8f, 14.0f), b2Vec2(0.0f, 0.0f), SimulationObject::SQUARE, SimulationMaterial::RUBBER, SimulationColor::TYPE::BLUE);
				addDynamicObject(b2Vec2(5.2f, 16.0f), b2Vec2(0.0f, 0.0f), SimulationObject::SQUARE, SimulationMaterial::RUBBER, SimulationColor::TYPE::BLUE);
				m_nNumberOfObjects--;
			}

			Simulation::Step(settings);

			if (terminateSimulation)
			{
				state.saveToJSONFile(m_world, "scene.json");
				FINISH_SIMULATION
			}
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

		SceneState state;

		void addDynamicObject(b2Vec2 position, b2Vec2 velocity, SimulationObject::TYPE objType, SimulationMaterial::TYPE materialType, SimulationColor color)
		{
			SimulationObject object = SimulationObject(objType);

			ShapePtr shape = object.getShape();

			SimulationMaterial mat = SimulationMaterial(materialType);

			b2BodyDef bd;
			bd.type = b2_dynamicBody;
			bd.position = position;
			bd.angle = RandomFloat(M_PI, M_PI);
			bd.linearVelocity = velocity;
			BODY* body = (BODY*)m_world->CreateBody(&bd);

			b2FixtureDef fd = b2FixtureDef();
			fd.density = mat.getDensity();
			fd.shape = shape.get();
			fd.restitution = mat.getRestitution();

			body->CreateFixture(&fd);

			body->setTexture(mat.getTexture());
			body->setColor(color.GetColor());

			state.add(ObjectState(body, mat.type, color.type, object.type));
		}

		void addStaticObject(b2Vec2 position, float32 angle, SimulationObject::TYPE objType, SimulationMaterial::TYPE materialType, SimulationColor color)
		{
			SimulationObject object = SimulationObject(objType);
			ShapePtr shape = object.getShape();
			SimulationMaterial mat = SimulationMaterial(materialType);
			b2BodyDef bd;
			bd.type = b2_staticBody;
			bd.position = position;
			bd.angle = angle;
			BODY* body = (BODY*)m_world->CreateBody(&bd);

			b2FixtureDef fd = b2FixtureDef();
			fd.density = mat.getDensity();
			fd.shape = shape.get();
			fd.restitution = mat.getRestitution();

			body->CreateFixture(&fd);

			body->setTexture(mat.getTexture());
			body->setColor(color.GetColor());

			state.add(ObjectState(body, mat.type, color.type, object.type));
		}

		void addStaticObject(b2Vec2 position, float32 angle, ShapePtr shape,
			SimulationObject::TYPE objType, SimulationMaterial::TYPE materialType, SimulationColor color)
		{
			SimulationObject object = SimulationObject(objType);
			SimulationMaterial material = SimulationMaterial(materialType);
			b2BodyDef bd;
			bd.type = b2_staticBody;
			bd.position = position;
			bd.angle = angle;
			BODY* body = (BODY*)m_world->CreateBody(&bd);
			body->CreateFixture(shape.get(), material.getDensity());
			body->setTexture(material.getTexture());
			body->setColor(color.GetColor());

			state.add(ObjectState(body, material.type, color.type, object.type));
		}


	};
}
