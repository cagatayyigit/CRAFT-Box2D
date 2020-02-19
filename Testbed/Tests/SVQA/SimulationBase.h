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
#include "CausalGraph.hpp"

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
            
            createBoundaries();
            
            m_pCausalGraph = CausalGraph::create();
            m_pCausalGraph->addEvent(StartEvent::create());
		}

		/// Derived simulations must call this in order to construct causal graph
		virtual void Step(SettingsBase* settings) override
        {
            Simulation::Step(settings);
            
            if(settings->terminate) {
                m_pCausalGraph->addEvent(EndEvent::create(m_stepCount));
                m_SceneJSONState.saveToJSONFile(m_world, "scene.json");
                FINISH_SIMULATION
            }
            
            detectStartTouchingEvents();
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
            const float friction = 0.5;
			std::vector<SimulationObject::TYPE> boundaries;
			boundaries.push_back(SimulationObject::LEFT_BOUNDARY);
			boundaries.push_back(SimulationObject::RIGHT_BOUNDARY);
			boundaries.push_back(SimulationObject::BOTTOM_BOUNDARY);

			for (auto&& bound : boundaries) {
				b2BodyDef bd;
				BODY* boundBody = (BODY*)m_world->CreateBody(&bd);
                
                SimulationObject boundaryObject = SimulationObject(bound);
                ShapePtr shape = boundaryObject.getShape();

				b2FixtureDef fd = b2FixtureDef();
				fd.friction = friction;
				fd.density = 0.0f;
				fd.shape = shape.get();
				boundBody->CreateFixture(&fd);
                
                auto objectState = ObjectState::create(boundBody, SimulationMaterial::UNKNOWN , SimulationColor::BLACK, bound);
                boundBody->SetUserData(objectState.get());

                m_SceneJSONState.add(objectState);
			}
		}

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
        
        void detectStartTouchingEvents()
        {
            for (auto it = m_Contacts.begin(); it != m_Contacts.end(); it++) {
                if (m_stepCount - it->step > COLLISION_DETECTION_STEP_DIFF) {
                    //DETECTED StartTouching_Event
                    m_pCausalGraph->addEvent(StartTouchingEvent::create(it->step, (BODY*)it->contact->GetFixtureA()->GetBody(),
                        (BODY*)it->contact->GetFixtureB()->GetBody()));
                    m_Contacts.erase(it--);
                }
            }
        }
        
        virtual void BeginContact(b2Contact* contact)  override {
            ContactInfo info;
            info.contact = contact;
            info.step = m_stepCount;

            m_Contacts.push_back(info);
        }
        
        virtual void EndContact(b2Contact* contact)  override {
            for (auto it = m_Contacts.begin(); it != m_Contacts.end(); it++) {
                if(it->contact == contact) {
                    if (m_stepCount - it->step > COLLISION_DETECTION_STEP_DIFF) {
                        //DETECTED EndTouching_Event
                        m_pCausalGraph->addEvent(EndTouchingEvent::create(it->step, (BODY*)it->contact->GetFixtureA()->GetBody(),
                            (BODY*)it->contact->GetFixtureB()->GetBody()));
                        
                    } else {
                        //DETECTED Collision_Event
                        m_pCausalGraph->addEvent(CollisionEvent::create(it->step, (BODY*)it->contact->GetFixtureA()->GetBody(),
                            (BODY*)it->contact->GetFixtureB()->GetBody()));
                    }
                    m_Contacts.erase(it--);
                }
                

            }
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
        
        struct ContactInfo
        {
            b2Contact* contact;
            int step;
        };

        std::vector<ContactInfo>    m_Contacts;
        
        CausalGraph::Ptr            m_pCausalGraph;
        SceneState                  m_SceneJSONState;
            
	};
}

#endif /* SimulationBase_h */
