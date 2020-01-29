#pragma once

#include "SimulationColor.h"
#include "Scene2Settings.h"
#include "SimulationBase.h"
#include "Box2D/Extension/b2VisBody.hpp"
#include "Box2D/Extension/b2VisPolygonShape.hpp"
#include <math.h> 

namespace svqa {
	class Scene2Simulation : public SimulationBase
	{
	public:
		typedef std::shared_ptr<Scene2Simulation> Ptr;
		Scene2Simulation(Scene2Settings::Ptr settings) : SimulationBase(settings)
		{
			m_nNumberOfObjects = 1;
			SET_FILE_OUTPUT_TRUE(m_pSettings->outputFilePath);

			createBoundaries(40.0f, 50.0f, 10.0f);
		}

		// Our "game loop".
		virtual void Step(SettingsBase* settings) override
		{
			const bool stable = isSceneStable();
			const bool addObject = stable && m_nNumberOfObjects > 0;
			const bool terminateSimulation = m_nNumberOfObjects == 0 && stable;

			if (addObject) {
				// Setup static objects.

				// Up  Floor
				addStaticObject(
					b2Vec2(5.0f, 20.0f),
					0,
					std::make_shared<b2PolygonShape>(SimulationObject::getRectangle(15.0f, 0.5f)),
					SimulationObject::CUSTOM_RECTANGLE,
					SimulationMaterial::METAL,
					SimulationColor::GRAY
				);

				// Down Floor
				addStaticObject(
					b2Vec2(0, 14.0f),
					0,
					std::make_shared<b2PolygonShape>(SimulationObject::getRectangle(10.0f, 0.5f)),
					SimulationObject::CUSTOM_RECTANGLE,
					SimulationMaterial::METAL,
					SimulationColor::GRAY
				);

				// First Rec
				addStaticObject(
					b2Vec2(20, 0.0f),
					0,
					std::make_shared<b2PolygonShape>(SimulationObject::getRectangle(1.5f, 6.0f)),
					SimulationObject::CUSTOM_RECTANGLE,
					SimulationMaterial::METAL,
					SimulationColor::GRAY
				);

				addDynamicObject(
					b2Vec2(20.0f, 14.0f),
					b2Vec2(0.0f, 0.0f),
					SimulationObject::SMALL_CIRCLE,
					SimulationMaterial::RUBBER,
					SimulationColor::TYPE::BLUE2
				);

				// Second Rec
				addStaticObject(
					b2Vec2(28, 0.0f),
					0,
					std::make_shared<b2PolygonShape>(SimulationObject::getRectangle(1.5f, 10.0f)),
					SimulationObject::CUSTOM_RECTANGLE,
					SimulationMaterial::METAL,
					SimulationColor::GRAY
				);

				addDynamicObject(
					b2Vec2(28.0f, 11.0f),
					b2Vec2(0.0f, 0.0f),
					SimulationObject::SMALL_CIRCLE,
					SimulationMaterial::RUBBER,
					SimulationColor::TYPE::GREEN2
				);

				// Third Rec
				addStaticObject(
					b2Vec2(35, -2.0f),
					0,
					std::make_shared<b2PolygonShape>(SimulationObject::getRectangle(1.5f, 4.0f)),
					SimulationObject::CUSTOM_RECTANGLE,
					SimulationMaterial::METAL,
					SimulationColor::GRAY
				);

				addDynamicObject(
					b2Vec2(35.0f, 4.0f),
					b2Vec2(0.0f, 0.0f),
					SimulationObject::SMALL_CIRCLE,
					SimulationMaterial::RUBBER,
					SimulationColor::TYPE::RED2
				);


				//
				// Curved Ramp
				//


				ShapePtr chainShape = std::make_shared<b2ChainShape>(SimulationObject::getCurve(
					[](float x) {
						return std::pow(x, 2);
					}, -2, 0.5, 0.05f
				));

				addStaticObject(
					b2Vec2(-35.0f, 14.0f),
					0,
					chainShape,
					SimulationObject::BIG_TRIANGLE,
					SimulationMaterial::METAL,
					SimulationColor::GRAY
				);



				// Circles
				// Stationary Bottom-Left

				addDynamicObject(
					b2Vec2(7.0f, 22.0f),
					b2Vec2(0.0f, 0.0f),
					SimulationObject::SMALL_CIRCLE,
					SimulationMaterial::RUBBER,
					SimulationColor::TYPE::RED2
				);

				addDynamicObject(
					b2Vec2(5.0f, 16.0f),
					b2Vec2(0.0f, 0.0f),
					SimulationObject::SMALL_CIRCLE,
					SimulationMaterial::RUBBER,
					SimulationColor::TYPE::BLUE2
				);

				addDynamicObject(
					b2Vec2(-30.0f, 42.0f),
					b2Vec2(0.0f, 0.0f),
					SimulationObject::SMALL_CIRCLE,
					SimulationMaterial::RUBBER,
					SimulationColor::TYPE::BLACK
				);


				m_nNumberOfObjects--;
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

		// TODO: We can embed these "addObject" methods in SimulationBase.h

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
			fd.friction = 100.0f;
			body->CreateFixture(&fd);

			body->setTexture(mat.getTexture());
			body->setColor(color.GetColor());

            auto objectState = ObjectState::create(body, mat.type, color.type, object.type);
            body->SetUserData(objectState.get());

            m_SceneJSONState.add(objectState);
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

            auto objectState = ObjectState::create(body, mat.type, color.type, object.type);
            body->SetUserData(objectState.get());

            m_SceneJSONState.add(objectState);
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
        
            auto objectState = ObjectState::create(body, material.type, color.type, object.type);
            body->SetUserData(objectState.get());

			m_SceneJSONState.add(objectState);
		}

	};
}
