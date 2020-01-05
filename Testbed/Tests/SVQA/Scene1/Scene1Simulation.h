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

				createBoundaries(40.0f, 50.0f);
		}

		// Our "game loop".
		virtual void Step(SettingsBase* settings) override
		{
			const bool stable = isSceneStable();
			const bool addObject = stable && m_nNumberOfObjects > 0;
			const bool terminateSimulation = false && stable;

			if (addObject) {

				// Setup static objects.
				//addStaticObject(VECTOR(5.0f, 5.0f), M_PI / 2, SimulationObject::BIG_RAMP, SimulationMaterial::METAL, SimulationColor::BLUE);
				addStaticObject(VECTOR(-30.0f, 3.0f), 0,
					std::make_shared<b2PolygonShape>(SimulationObject::getRectangle(30.0f, 1.0f)), SimulationObject::CUSTOM_RECTANGLE,
					SimulationMaterial::METAL, SimulationColor::BROWN);

				addStaticObject(VECTOR(35.0f, 3.0f), 0,
					std::make_shared<b2PolygonShape>(SimulationObject::getRectangle(25.0f, 1.0f)), SimulationObject::CUSTOM_RECTANGLE,
					SimulationMaterial::METAL, SimulationColor::BROWN);

				addStaticObject(VECTOR(-26.0f, 5.0f), M_PI , SimulationObject::BIG_TRIANGLE,
					SimulationMaterial::METAL, SimulationColor::BROWN);

				addStaticObject(VECTOR(-10.0f, 33.0f), 0,
					std::make_shared<b2PolygonShape>(SimulationObject::getRectangle(10.0f, 1.0f,VECTOR(15.0f,0.5f),M_PI / 4)), SimulationObject::CUSTOM_RECTANGLE,
					SimulationMaterial::METAL, SimulationColor::BROWN);

				addStaticObject(VECTOR(-40.0f, 25.0f), 0,
					std::make_shared<b2PolygonShape>(SimulationObject::getRectangle(-5.0f, 1.0f, VECTOR(17.0f, 6.5f), -M_PI / 4)), SimulationObject::CUSTOM_RECTANGLE,
					SimulationMaterial::METAL, SimulationColor::BROWN);

				addDynamicObject(VECTOR(-30.0f, -3.0f), VECTOR(15.0f, 0.0f), SimulationObject::SMALL_CIRCLE, SimulationMaterial::RUBBER, SimulationColor::TYPE::BLUE);
				addDynamicObject(VECTOR(30.0f, -3.0f), VECTOR(-15.0f, 0.0f), SimulationObject::SMALL_CIRCLE, SimulationMaterial::RUBBER, SimulationColor::TYPE::BLUE);
				addDynamicObject(VECTOR(30.0f, 6.0f), VECTOR(-15.0f, 0.0f), SimulationObject::SMALL_CIRCLE, SimulationMaterial::RUBBER, SimulationColor::TYPE::BLUE);
				addDynamicObject(VECTOR(-25.0f, 40.0f), VECTOR(0.0f, -5.0f), SimulationObject::SMALL_CIRCLE, SimulationMaterial::RUBBER, SimulationColor::TYPE::BLUE);

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
			body->CreateFixture(shape.get(), mat.getDensity());

			body->setTexture(mat.getTexture());
			body->setColor(color.GetColor());

			state.add(ObjectState(body, mat.type, color.type, object.type));
		}

		void addStaticObject(VECTOR position, float32 angle, SimulationObject::TYPE objType, SimulationMaterial::TYPE materialType, SimulationColor color)
		{
			SimulationObject object = SimulationObject(objType);
			ShapePtr shape = object.getShape();
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