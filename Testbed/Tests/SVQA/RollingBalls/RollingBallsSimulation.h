#pragma once

#include "SimulationColor.h"
#include "RollingBallsSettings.h"
#include "SimulationBase.h"
#include "Box2D/Extension/b2VisBody.hpp"
#include "Box2D/Extension/b2VisPolygonShape.hpp"
#include <math.h> 

namespace svqa {
	class RollingBallsSimulation : public SimulationBase
	{
	public:
		typedef std::shared_ptr<RollingBallsSimulation> Ptr;
		RollingBallsSimulation(RollingBallsSettings::Ptr settings) : SimulationBase(settings)
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
			const bool terminateSimulation = false; // m_nNumberOfObjects == 0 && stable;

			if (addObject) {
				// Setup static objects.

				b2Vec2 rampPosition = b2Vec2(RandomFloatFromHardware(-36.5f, -33.5f), 4.0f);

				float32 min_angle1 = M_PI / 7.0f;
				float32 max_angle1 = M_PI / 2.0f - min_angle1;
				float32 min_angle2 = M_PI / 2.0f + min_angle1;
				float32 max_angle2 = M_PI / 2.0f + max_angle1;
				std::vector<float32> mins = std::vector<float32>();
				mins.push_back(min_angle1);
				mins.push_back(min_angle2);
				std::vector<float32> maxs = std::vector<float32>();
				maxs.push_back(max_angle1);
				maxs.push_back(max_angle2);

				float32 angle = RandomFloatWithinRanges(mins, maxs);

				float32 leftFloorLen = (RandomFloatFromHardware(15.0, 18.0));
				float32 rightFloorCoorX = (RandomFloatFromHardware(40.0, 46.0));

				float32 leftBottomCircleCoorX = (RandomFloatFromHardware(-30.0, 10.0));
				float32 rightBottomCircleCoorX = (RandomFloatFromHardware(12.0, 30.0));

				float32 inclinedFloorLen = (RandomFloatFromHardware(9.0, 12.0));
				float32 circleV = (RandomFloatFromHardware(-5.0, -15.0));


				// Left  Floor
				addStaticObject(
					b2Vec2(-16.0f, 3.0f),
					0,
					std::make_shared<b2PolygonShape>(SimulationObject::getRectangle(leftFloorLen, 1.0f)),
					SimulationObject::CUSTOM_RECTANGLE,
					SimulationMaterial::METAL,
					SimulationColor::GRAY
				);

				// Right Floor
				addStaticObject(
					b2Vec2(rightFloorCoorX, 3.0f),
					0,
					std::make_shared<b2PolygonShape>(SimulationObject::getRectangle(35.0f, 1.0f)),
					SimulationObject::CUSTOM_RECTANGLE,
					SimulationMaterial::METAL,
					SimulationColor::GRAY
				);


				// Inclined Floor
				addStaticObject(
					b2Vec2(-28.0f, 35.0f),
					angle,
					std::make_shared<b2PolygonShape>(SimulationObject::getRectangle(6.0f, 0.5f)),
					SimulationObject::CUSTOM_RECTANGLE,
					SimulationMaterial::METAL,
					SimulationColor::GRAY
				);

				// Inclined Floor
				addStaticObject(
					b2Vec2(-10.0f, 25.0f),
					M_PI / 4,
					std::make_shared<b2PolygonShape>(SimulationObject::getRectangle(inclinedFloorLen, 1.0f)),
					SimulationObject::CUSTOM_RECTANGLE,
					SimulationMaterial::METAL,
					SimulationColor::GRAY
				);

				// Big Ramp
				addStaticObject(
					rampPosition,
					0,
					std::make_shared<b2PolygonShape>(SimulationObject::getRightTriangle(25, 20)),
					SimulationObject::BIG_TRIANGLE,
					SimulationMaterial::METAL,
					SimulationColor::PURPLE
				);

				// Small Ramp
				addStaticObject(
					b2Vec2(-40.0f, -6.0f),
					0,
					std::make_shared<b2PolygonShape>(SimulationObject::getRightTriangle(3, 3)),
					SimulationObject::BIG_TRIANGLE,
					SimulationMaterial::METAL,
					SimulationColor::PURPLE
				);


				// Circles
				// Stationary Bottom-Left
				addDynamicObject(
					b2Vec2(leftBottomCircleCoorX, -3.0f),
					b2Vec2(0.0f, 0.0f),
					SimulationObject::SMALL_CIRCLE,
					SimulationMaterial::RUBBER,
					SimulationColor::TYPE::CYAN
				);

				// Stationary Bottom-Right
				addDynamicObject(
					b2Vec2(rightBottomCircleCoorX, -3.0f),
					b2Vec2(0.0f, 0.0f),
					SimulationObject::SMALL_CIRCLE,
					SimulationMaterial::RUBBER,
					SimulationColor::TYPE::PURPLE
				);

				// Moving on the Right Floor
				addDynamicObject(
					b2Vec2(30.0f, 6.0f),
					b2Vec2(circleV, 0.0f),
					SimulationObject::SMALL_CIRCLE,
					SimulationMaterial::RUBBER,
					SimulationColor::TYPE::RED
				);

				addDynamicObject(
					b2Vec2(-30.0f, 42.0f),
					b2Vec2(0.0f, 0.0f),
					SimulationObject::BIG_CIRCLE,
					SimulationMaterial::RUBBER,
					SimulationColor::TYPE::BLUE
				);


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
