#pragma once

#include "SimulationColor.h"
#include "Scene1Settings.h"
#include "SimulationBase.h"
#include "Box2D/Extension/b2VisBody.hpp"
#include "Box2D/Extension/b2VisPolygonShape.hpp"
#include <math.h> 

namespace svqa {
	class Scene1Simulation : public SimulationBase
	{
	public:
		typedef std::shared_ptr<Scene1Simulation> Ptr;
		Scene1Simulation(Scene1Settings::Ptr settings) : SimulationBase(settings)
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

				VECTOR rampPosition = VECTOR(RandomFloatFromHardware(-36.5f, -33.5f), 4.0f);

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

				// Left  Floor
				addStaticObject(
					VECTOR(-18.0f, 3.0f),
					0,
					std::make_shared<b2PolygonShape>(SimulationObject::getRectangle(15.0f, 1.0f)),
					SimulationObject::CUSTOM_RECTANGLE,
					SimulationMaterial::METAL,
					SimulationColor::GRAY
				);

				// Right Floor
				addStaticObject(
					VECTOR(22.5f, 3.0f),
					0,
					std::make_shared<b2PolygonShape>(SimulationObject::getRectangle(15.0f, 1.0f)),
					SimulationObject::CUSTOM_RECTANGLE,
					SimulationMaterial::METAL,
					SimulationColor::GRAY
				);


				// Inclined Floor
				addStaticObject(
					VECTOR(-28.0f, 35.0f),
					angle,
					std::make_shared<b2PolygonShape>(SimulationObject::getRectangle(6.0f, 0.5f)),
					SimulationObject::CUSTOM_RECTANGLE,
					SimulationMaterial::METAL,
					SimulationColor::GRAY
				);

				// Inclined Floor
				addStaticObject(
					VECTOR(-10.0f, 25.0f),
					M_PI / 4,
					std::make_shared<b2PolygonShape>(SimulationObject::getRectangle(10.0f, 1.0f)),
					SimulationObject::CUSTOM_RECTANGLE,
					SimulationMaterial::METAL,
					SimulationColor::GRAY
				);

				// Ramp
				addStaticObject(
					rampPosition,
					0,
					std::make_shared<b2PolygonShape>(SimulationObject::getRightTriangle(25, 20)),
					SimulationObject::BIG_TRIANGLE,
					SimulationMaterial::METAL,
					SimulationColor::PURPLE
				);




				// Circles
				addDynamicObject(
					VECTOR(-30.0f, -3.0f),
					VECTOR(0.0f, 0.0f),
					SimulationObject::SMALL_CIRCLE,
					SimulationMaterial::RUBBER,
					SimulationColor::TYPE::CYAN
				);

				addDynamicObject(
					VECTOR(30.0f, -3.0f),
					VECTOR(0.0f, 0.0f),
					SimulationObject::SMALL_CIRCLE,
					SimulationMaterial::RUBBER,
					SimulationColor::TYPE::PURPLE
				);

				addDynamicObject(
					VECTOR(30.0f, 6.0f),
					VECTOR(-20.0f, 0.0f),
					SimulationObject::SMALL_CIRCLE,
					SimulationMaterial::RUBBER,
					SimulationColor::TYPE::RED
				);

				addDynamicObject(
					VECTOR(-30.0f, 42.0f),
					VECTOR(0.0f, 0.0f),
					SimulationObject::BIG_CIRCLE,
					SimulationMaterial::RUBBER,
					SimulationColor::TYPE::BLUE
				);

				addDynamicObject(
					VECTOR(-38.0f, 38.0f),
					VECTOR(0.0f, 0.0f),
					SimulationObject::SMALL_CIRCLE,
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
		VECTOR m_vMovingObjPosition;
		VECTOR m_vStagnantObjPosition;
		VECTOR m_vObstaclePosition;
		VECTOR m_vInitialDropVelocity;

		SceneState state;

		void addDynamicObject(VECTOR position, VECTOR velocity, SimulationObject::TYPE objType, SimulationMaterial::TYPE materialType, SimulationColor color)
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

		void addStaticObject(VECTOR position, float32 angle, SimulationObject::TYPE objType, SimulationMaterial::TYPE materialType, SimulationColor color)
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

		void addStaticObject(VECTOR position, float32 angle, ShapePtr shape,
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