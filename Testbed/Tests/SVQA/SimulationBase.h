//
//  SimulationBase.h
//  Testbed
//
//  Created by Tayfun Ateş on 24.11.2019.
//

#ifndef SimulationBase_h
#define SimulationBase_h

#include "Simulation.h"
#include "Settings.h"
#include "SimulationID.h"
#include "CausalEventListener.hpp"

#ifdef _MSC_VER
#define _USE_MATH_DEFINES
#endif
#include <math.h>

namespace svqa {
#define SET_FILE_OUTPUT_FALSE ((SimulationRenderer*)((b2VisWorld*)m_world)->getRenderer())->setFileOutput(false);
#define SET_FILE_OUTPUT_TRUE(X) ((SimulationRenderer*)((b2VisWorld*)m_world)->getRenderer())->setFileOutput((X), m_pSettings->bufferWidth, m_pSettings->bufferHeight);
#define FINISH_SIMULATION {((SimulationRenderer*)((b2VisWorld*)m_world)->getRenderer())->Finish(); exit(0);};

	class SimulationBase : public Simulation
	{
	public:
		typedef std::shared_ptr<SimulationBase> Ptr;

		SimulationBase(Settings::Ptr _settings_)
		{
			m_pSettings = _settings_;
			m_nDistinctColorUsed = 8;
		}

		/// Derived simulations must call this in order to construct causal graph
		virtual void Step(SettingsBase* settings)
        {
            Simulation::Step(settings);
            CausalEventListener::getCurrentEvents(m_stepCount, m_world);
        }

		/// Gets the common settings object
		Settings::Ptr getSettings()
		{
			return m_pSettings;
		}

		/// Name of the simulation
		/// Derived simulations must have names
		virtual SimulationID getIdentifier() = 0;

	protected:
		Settings::Ptr m_pSettings;
		unsigned short m_nDistinctColorUsed;

		int randWithBound(const int& bound)
		{
			return (rand() & (RAND_LIMIT)) % bound;
		}

		virtual bool isSceneStable()
		{
			b2Body* bodies = m_world->GetBodyList();
			for (b2Body* b = bodies; b; b = b->GetNext())
			{
				if (b->IsAwake() && !(b->GetType() == b2_staticBody)) {
					return false;
				}
			}
			return true;
		}

		virtual void createBoundaries()
		{
			std::vector<std::pair<b2Vec2, b2Vec2>> boundaries;
			boundaries.push_back(std::make_pair(b2Vec2(-40.0f, 0.0f), b2Vec2(40.0f, 0.0f)));
			boundaries.push_back(std::make_pair(b2Vec2(-30.0f, 0.0f), b2Vec2(-30.0f, 50.0f)));
			boundaries.push_back(std::make_pair(b2Vec2(30.0f, 0.0f), b2Vec2(30.0f, 50.0f)));

			for (auto&& bound : boundaries) {
				b2BodyDef bd;
				BODY* boundBody = (BODY*)m_world->CreateBody(&bd);
				b2EdgeShape shape;
				shape.Set(bound.first, bound.second);
				boundBody->CreateFixture(&shape, 0.0f);
			}
		}

		virtual void createBoundaries(float32 x, float32 y)
		{
			std::vector<std::pair<b2Vec2, b2Vec2>> boundaries;
			boundaries.push_back(std::make_pair(b2Vec2(-x, -5.0f), b2Vec2(x, -5.0f)));
			boundaries.push_back(std::make_pair(b2Vec2(-x, -5.0f), b2Vec2(-x, y)));
			boundaries.push_back(std::make_pair(b2Vec2(x, -5.0f), b2Vec2(x, y)));

			for (auto&& bound : boundaries) {
				b2BodyDef bd;
				BODY* boundBody = (BODY*)m_world->CreateBody(&bd);
				b2EdgeShape shape;
				shape.Set(bound.first, bound.second);
				boundBody->CreateFixture(&shape, 0.0f);
			}
		}

		virtual void createBoundaries(float32 x, float32 y, float32 friction)
		{
			std::vector<std::pair<b2Vec2, b2Vec2>> boundaries;
			boundaries.push_back(std::make_pair(b2Vec2(-x, -5.0f), b2Vec2(x, -5.0f)));
			boundaries.push_back(std::make_pair(b2Vec2(-x, -5.0f), b2Vec2(-x, y)));
			boundaries.push_back(std::make_pair(b2Vec2(x, -5.0f), b2Vec2(x, y)));

			for (auto&& bound : boundaries) {
				b2BodyDef bd;
				BODY* boundBody = (BODY*)m_world->CreateBody(&bd);
				b2EdgeShape shape;
				shape.Set(bound.first, bound.second);
				b2FixtureDef fd = b2FixtureDef();
				fd.friction = friction;
				fd.density = 0.0f;
				fd.shape = &shape;
				boundBody->CreateFixture(&fd);
			}
		}

		virtual void createImmediateInitialScene(const size_t& numberOfObjects,
			const std::vector<SimulationObject::TYPE>& objectTypes,
			const b2Vec2& throwMinPos,
			const b2Vec2& throwMaxPos,
			const b2Vec2& dropVelocity)
		{
			float32 timeStep = m_pSettings->hz > 0.0f ? 1.0f / m_pSettings->hz : float32(0.0f);
			for (size_t i = 0; i < numberOfObjects; i++) {
				addSceneObject(objectTypes, throwMinPos, throwMaxPos, dropVelocity);
				while (!isSceneStable()) {
					m_world->Step(timeStep, m_pSettings->velocityIterations, m_pSettings->positionIterations);
				}
			}
		}
        
        virtual void BeginContact(b2Contact* contact)  override {
            int a = 2;
            int b = a;
        }
        virtual void EndContact(b2Contact* contact)  override {
            int a = 2;
            int b = a;
        }

		virtual ObjectState addSceneObject(const std::vector<SimulationObject::TYPE>& objectTypes,
			const b2Vec2& throwMinPos,
			const b2Vec2& throwMaxPos,
			const b2Vec2& dropVelocity)
		{
			float posX = RandomFloat(throwMinPos.x, throwMaxPos.x);
			float posY = RandomFloat(throwMinPos.y, throwMaxPos.y);

			int objectIndex = randWithBound(objectTypes.size());
			SimulationObject object = SimulationObject(objectTypes[objectIndex]);

			ShapePtr shape = object.getShape();

			int materialIndex = randWithBound(2);
			SimulationMaterial mat = SimulationMaterial((SimulationMaterial::TYPE) materialIndex);

			b2BodyDef bd;
			bd.angle = M_PI / 4;
			bd.type = b2_dynamicBody;
			bd.position = b2Vec2(posX, posY);
			bd.linearVelocity = dropVelocity;
			BODY* body = (BODY*)m_world->CreateBody(&bd);
			body->CreateFixture(shape.get(), mat.getDensity());

			int colorIndex = randWithBound(m_nDistinctColorUsed);
			SimulationColor col = SimulationColor((SimulationColor::TYPE) colorIndex);
			body->setTexture(mat.getTexture());
			body->setColor(col.GetColor());

			return ObjectState(body, mat.type, col.type, object.type);
		}
	};
}

#endif /* SimulationBase_h */
