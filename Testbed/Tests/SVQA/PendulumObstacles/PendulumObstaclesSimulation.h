//
//  PendulumObstaclesSimulation.h
//  Testbed
//
//  Created by Tayfun Ateş on 25.11.2019.
//

#ifndef PendulumObstaclesSimulation_h
#define PendulumObstaclesSimulation_h

#include "SimulationColor.h"
#include "PendulumObstaclesSettings.h"
#include "SimulationBase.h"
#include "Box2D/Extension/b2VisBody.hpp"
#include "Box2D/Extension/b2VisPolygonShape.hpp"
#include <math.h>

namespace svqa {
	class PendulumObstaclesSimulation : public SimulationBase
	{
	public:
		typedef std::shared_ptr<PendulumObstaclesSimulation> Ptr;

		PendulumObstaclesSimulation(PendulumObstaclesSettings::Ptr _settings_) : SimulationBase(_settings_)
		{
			m_nNumberOfObjects = _settings_->numberOfObjects;
			m_nNumberOfObstacles = _settings_->numberOfObstacles;

			m_vInitialDropVelocity = b2Vec2(0.0f, -20.0f);

			m_fMaxRopeLength = 15.0f;

			m_vThrowMin = b2Vec2(-30.0f, 50.0f);
			m_vThrowMax = b2Vec2(30.0f, 50.0f);

			m_vObstacleMin = b2Vec2(-30.0f, 0.0f);
			m_vObstacleMax = b2Vec2(30.0f, 40.0f);

			SET_FILE_OUTPUT_TRUE(m_pSettings->outputVideoPath)
		}

		void InitializeScene() override {
			// Obstacles are created in step since it requires GL context to be initialized
			createObstacles();

			for (int i = 0; i < m_nNumberOfObjects; i++) {
				addSimulationObject();
			}
		}

		virtual SimulationID getIdentifier() override
		{
			return SimulationID::ID_PendulumObstacles;
		}

	private:

		void createObstacles()
		{
			for (int i = 0; i < m_nNumberOfObstacles; i++) {
				while (!createObstacle()) {

				}
			}
		}

		BODY* createRopeUnit(const b2Vec2& pos)
		{
			SimulationObject object = SimulationObject(SimulationObject::ROPE_UNIT);
			ShapePtr shape = object.getShape();

			SimulationMaterial mat = SimulationMaterial(SimulationMaterial::RUBBER);

			b2BodyDef bd;
			bd.angle = M_PI / 4;
			bd.type = b2_dynamicBody;
			bd.position = pos;

			BODY* pin = (BODY*)m_world->CreateBody(&bd);
			//            b2FixtureDef fd;
			//            fd.shape = shape.get();
			//            fd.density = 1.0f; //Kind of elasticity of the rope
			//            fd.friction = 0.2f;
			pin->CreateFixture(shape.get(), 50.0f);

			SimulationColor col = SimulationColor(SimulationColor::GRAY);
			pin->setTexture(mat.getTexture());
			pin->setColor(col.GetColor());

			return pin;
		}

		BODY* createPin()
		{
			SimulationObject object = SimulationObject(SimulationObject::WALL_PIN);
			ShapePtr shape = object.getShape();

			float posX, posY;
			posX = RandomFloat(m_vObstacleMin.x, m_vObstacleMax.x);
			posY = RandomFloat(m_vObstacleMin.y, m_vObstacleMax.y);

			SimulationMaterial mat = SimulationMaterial(SimulationMaterial::RUBBER);

			b2BodyDef bd;
			bd.angle = M_PI / 4;
			bd.type = b2_staticBody;
			//bd.position = b2Vec2(pinPosition.x+pinOffset.x,pinPosition.y+yOffset);
			bd.position = b2Vec2(posX, posY);

			BODY* weight = (BODY*)m_world->CreateBody(&bd);

			b2FixtureDef fd;
			fd.shape = shape.get();
			fd.density = mat.getDensity();
			fd.friction = 0.2f;
			weight->CreateFixture(&fd);

			int colorIndex = randWithBound(m_nDistinctColorUsed);
			SimulationColor col = SimulationColor((SimulationColor::TYPE) colorIndex);
			weight->setTexture(mat.getTexture());
			weight->setColor(col.GetColor());

			return weight;
		}

		b2Joint* createJoint(BODY* pin, BODY* weight, float length)
		{
			b2RopeJointDef jd;
			jd.maxLength = length;
			jd.collideConnected = true;
			b2Vec2 p1, p2, d;

			//            jd.frequencyHz = 2.0f;
			//            jd.dampingRatio = 0.0f;
						//jd.type = e_distanceJoint;

			jd.bodyA = pin;
			jd.bodyB = weight;
			jd.localAnchorA.Set(0.0f, 0.0f);
			jd.localAnchorB.Set(0.0f, 0.0f);;
			p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
			p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
			d = p2 - p1;
			b2Joint* joint = m_world->CreateJoint(&jd);
			return joint;
		}

		b2Vec2 lerp(b2Vec2 vectorStart, b2Vec2 vectorEnd, float t)
		{
			b2Vec2 v = { vectorStart.x + ((vectorEnd.x - vectorStart.x) * t),
							 vectorStart.y + ((vectorEnd.y - vectorStart.y) * t) };
			return v;
		}

		bool createObstacle()
		{
			SimulationObject object = SimulationObject(SimulationObject::WALL_PIN);
			b2VisPolygonShape pin = *(std::static_pointer_cast<b2VisPolygonShape>(object.getShape()));
			const float edgeLength = fabs(pin.m_vertices[0].x - pin.m_vertices[1].x);

			BODY* pin1 = createPin();
			BODY* pin2 = createPin();
			while (b2Distance(pin2->GetPosition(), pin1->GetPosition()) > m_fMaxRopeLength) {
				m_world->DestroyBody(pin2);
				pin2 = createPin();
			}
			const auto& currDistance = b2Distance(pin2->GetPosition(), pin1->GetPosition());
			const size_t dynamicPinCount = (size_t)fabs(currDistance / edgeLength);

			const auto& p1 = pin1->GetPosition();
			const auto& p2 = pin2->GetPosition();

			BODY* prev = pin1;

			for (size_t i = 0; i < dynamicPinCount; i++) {
				BODY* dynamicPin = createRopeUnit(lerp(p1, p2, float(i) / dynamicPinCount));
				b2Joint* joint = createJoint(prev, dynamicPin, edgeLength);
				prev = dynamicPin;
			}
			createJoint(prev, pin2, edgeLength);
			//m_world->Step(0.0f, 0, 0);



//            b2ContactEdge* contact = dynamicObstacle->GetContactList();
//            if(contact) {
//                m_world->DestroyBody(dynamicObstacle);
//                return false;
//            } else {
//                m_world->DestroyBody(dynamicObstacle);
//                b2BodyDef bd;
//                bd.type = b2_staticBody;
//                bd.position = b2Vec2(posX,posY);
//                bd.angle = orientation;
//
//                BODY* staticObstacle = (BODY*) m_world->CreateBody(&bd);
//                staticObstacle->CreateFixture(&shape, mat.getDensity());
//
//                int colorIndex = randWithBound(m_nDistinctColorUsed);
//                SimulationColor col = SimulationColor((SimulationColor::TYPE) colorIndex);
//                staticObstacle->setTexture(mat.getTexture());
//                staticObstacle->setColor(col.GetColor(mat.type));
//
//                state.add(ObjectState(staticObstacle, mat.type, col.type, object.type));
//            }
			return true;
		}

		int m_nNumberOfObjects;
		int m_nNumberOfObstacles;
		float m_fMaxRopeLength;
		b2Vec2 m_vThrowMin;
		b2Vec2 m_vThrowMax;
		b2Vec2 m_vObstacleMin;
		b2Vec2 m_vObstacleMax;
		b2Vec2 m_vInitialDropVelocity;

		const std::vector<SimulationObject::TYPE> m_vSimulationObjectTypes = { SimulationObject::SMALL_CUBE, SimulationObject::BIG_CUBE, SimulationObject::SMALL_HEXAGON, SimulationObject::BIG_HEXAGON,
			SimulationObject::SMALL_TRIANGLE, SimulationObject::BIG_TRIANGLE };

		void addSimulationObject()
		{
			float posX = RandomFloat(m_vThrowMin.x, m_vThrowMax.x);
			float posY = RandomFloat(m_vThrowMin.y, m_vThrowMax.y);

			int objectIndex = randWithBound(m_vSimulationObjectTypes.size());
			SimulationObject object = SimulationObject(m_vSimulationObjectTypes[objectIndex]);

			ShapePtr shape = object.getShape();

			SimulationMaterial mat = SimulationMaterial(SimulationMaterial::METAL);

			b2BodyDef bd;
			bd.type = b2_dynamicBody;
			bd.position = b2Vec2(posX, posY);
			bd.linearVelocity = m_vInitialDropVelocity;
			BODY* body = (BODY*)m_world->CreateBody(&bd);
			body->CreateFixture(shape.get(), mat.getDensity());

			int colorIndex = randWithBound(m_nDistinctColorUsed);
			SimulationColor col = SimulationColor((SimulationColor::TYPE) colorIndex);
			body->setTexture(mat.getTexture());
			body->setColor(col.GetColor());

			auto objectState = ObjectState::create(body, mat.type, col.type, object.type);
			body->SetUserData(objectState.get());

			m_SceneJSONState.add(objectState);
		}
	};
}

#endif /* PendulumObstaclesSimulation_h */
