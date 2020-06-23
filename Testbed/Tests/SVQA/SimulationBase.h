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
#include "SceneState.h"

#define LOG(str) std::cout << "[LOG] " << str << std::endl
#define LOG_PROGRESS(str, progress) std::cout << "[LOG] " << str << " " << progress <<  "\r"

namespace svqa {
#define SET_FILE_OUTPUT_FALSE ((SimulationRenderer*)((b2VisWorld*)m_world)->getRenderer())->setFileOutput(false);
#define SET_FILE_OUTPUT_TRUE(X) ((SimulationRenderer*)((b2VisWorld*)m_world)->getRenderer())->setFileOutput((X), m_pSettings->bufferWidth, m_pSettings->bufferHeight);
#define FINISH_SIMULATION {((SimulationRenderer*)((b2VisWorld*)m_world)->getRenderer())->Finish(); exit(0);};

	// TODO: This class has started to become a God-object, maybe break it apart?
	class SimulationBase : public Simulation
	{
	private:
		std::vector<std::vector<int>> scs; // scs: size color shape 

	public:
		typedef std::shared_ptr<SimulationBase> Ptr;

		SimulationBase(Settings::Ptr _settings_)
		{
			m_pSettings = _settings_;
			m_nDistinctColorUsed = 8;

			m_pCausalGraph = CausalGraph::create();
			m_pCausalGraph->addEvent(StartEvent::create());
			m_bGeneratingFromJSON = m_pSettings->inputScenePath.compare("") != 0;

			if (!isGeneratingFromJSON()) {
				CreateBoundaries();
			}
		}

		/// Derived simulations must call this in order to construct causal graph
		virtual void Step(SettingsBase* settings) override
		{
			LOG_PROGRESS("Step Count:", std::to_string(m_StepCount) + "/" + std::to_string(m_pSettings->stepCount));

			if (!isSceneInitialized()) {
				LOG("Initializing simulation objects...");

				// Generate scene from JSON file if inputScenePath is not blank and the scene is not already generated.
				if (isGeneratingFromJSON() && !m_bSceneRegenerated) {
					GenerateSceneFromJson(m_pSettings->inputScenePath);
				}
				else InitializeScene();

				setSceneInitialized(true);
			}

			// Take snapshot of the scene in the beginning of the simulation.
			if (isSceneInitialized() && !m_bSceneSnapshotTaken) {
				m_StartSceneStateJSON = SimulationBase::GetSceneStateJSONObject(m_SceneJSONState, m_StepCount);
				m_bSceneSnapshotTaken = true;
			}

			Simulation::Step(settings);

			if (shouldTerminateSimulation()) {
				m_EndSceneStateJSON = SimulationBase::GetSceneStateJSONObject(m_SceneJSONState, m_StepCount);
				TerminateSimulation();
			}

			DetectStartTouchingEvents();
		}

		/// Gets the common settings object
		Settings::Ptr getSettings()
		{
			return m_pSettings;
		}

		/// Name of the simulation
		/// Derived simulations must have names
		virtual SimulationID getIdentifier() = 0;

		bool isSceneInitialized() {
			return m_bSceneInitialized;
		}

		void setSceneInitialized(bool value) {
			m_bSceneInitialized = value;
		}

		bool isGeneratingFromJSON() {
			return m_bGeneratingFromJSON;
		}

		virtual void InitializeScene() = 0;

		virtual bool shouldTerminateSimulation() {
			return m_StepCount == m_pSettings->stepCount;
		}

		void TakeSceneSnapshot(std::string filename) {
			LOG("Taking snapshot of the current world state...");
			m_SceneJSONState.saveToJSONFile(m_world, filename);
		}

		void TerminateSimulation() {
			LOG("Terminating simulation...");

			m_pCausalGraph->addEvent(EndEvent::create(m_StepCount));

			json output_json;

			output_json.emplace("causal_graph", m_pCausalGraph->toJSON());

			auto scene_states_json = json::array();
			scene_states_json.push_back(m_StartSceneStateJSON);
			scene_states_json.push_back(m_EndSceneStateJSON);

			output_json.emplace("scene_states", scene_states_json);
			output_json.emplace("video_filename", m_pSettings->outputVideoPath);

			JSONHelper::saveJSON(output_json, 2, m_pSettings->outputJSONPath);

			FINISH_SIMULATION
		}

		void GenerateSceneFromJson(std::string filename) {
			LOG("Generating scene from \"" + filename + "\"...");

			json j;
			bool fileLoadRes = JSONHelper::loadJSON(j, filename);
			if (fileLoadRes) {
				auto sceneStatesItr = j.find("scene_states");
				if (sceneStatesItr != j.end()) {
					for (const auto& sceneJson : *sceneStatesItr) {
						int step;
						sceneJson.at("step").get_to(step);
						if (step == 0) {
							m_SceneJSONState.loadFromJSON(*sceneJson.find("scene"), m_world);
							m_bSceneRegenerated = true;
							break;
						}
					}
				}
			}
		}

		static json GetSceneStateJSONObject(SceneState state, int stepCount) {
			json obj = json::object();
			obj.emplace("step", stepCount);
			obj.emplace("scene", state.toJSON());
			return obj;
		}

	protected:
		Settings::Ptr	m_pSettings;
		unsigned short	m_nDistinctColorUsed;
		bool			m_bSceneRegenerated;
		bool			m_bSceneInitialized;
		bool			m_bGeneratingFromJSON;
		bool			m_bSceneSnapshotTaken;

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

		virtual void AddTargetBasket(b2Vec2 pos, float angleInRadians)
		{
			SimulationObject basketObject = SimulationObject(SimulationObject::STATIC_BASKET, SimulationObject::BLACK, SimulationObject::LARGE);

			b2BodyDef bd;
			bd.position = pos;
			bd.angle = angleInRadians;

			BODY *basketBody = (BODY*)m_world->CreateBody(&bd);

#if !USE_DEBUG_DRAW
			basketBody->setColor(basketObject.getColor());
#endif

			ShapePtr shape = basketObject.getShape();

			b2FixtureDef fd = b2FixtureDef();
			fd.friction = basketObject.getFriction();
			fd.density = basketObject.getDensity();
			fd.restitution = basketObject.getRestitution();
			fd.shape = shape.get();
			basketBody->CreateFixture(&fd);

			auto objectState = ObjectState::create(basketBody, basketObject.mShape, basketObject.mColor, basketObject.mSize);
			basketBody->SetUserData(objectState.get());

			m_SceneJSONState.add(objectState);

			// TODO: Code duplication: When we are trying to re-generate a simulation, we are adding sensor body from ObjectState.h.
			b2Vec2* vertices = ((b2ChainShape*)fd.shape)->m_vertices;

			b2Vec2 sensorVertices[4];
			std::copy(vertices, vertices + 4, sensorVertices);
			for (int i = 0; i < 4; i++)
			{
				sensorVertices[i] *= 0.99f; // To not detect container event from the outside of the container.
			}

			ObjectState::AddSensorBody(m_world, SimulationObject::SENSOR_BASKET, pos, angleInRadians, sensorVertices, 4, basketBody, b2Color(0.9f, 0.9f, 0.9f));
		}

		virtual void CreateBoundaries()
		{
			std::vector<SimulationObject::Shape> boundaries;
			boundaries.push_back(SimulationObject::STATIC_LEFT_BOUNDARY);
			boundaries.push_back(SimulationObject::STATIC_RIGHT_BOUNDARY);
			boundaries.push_back(SimulationObject::STATIC_BOTTOM_BOUNDARY);

			for (auto bound : boundaries) {
				b2BodyDef bd;
				BODY* boundBody = (BODY*)m_world->CreateBody(&bd);

				SimulationObject boundaryObject = SimulationObject(bound, SimulationObject::BLACK, SimulationObject::LARGE);
#if !USE_DEBUG_DRAW
				boundBody->setColor(boundaryObject.getColor());
#endif

				ShapePtr shape = boundaryObject.getShape();

				b2FixtureDef fd = b2FixtureDef();
				fd.friction = boundaryObject.getFriction();
				fd.density = boundaryObject.getDensity();
				fd.restitution = boundaryObject.getRestitution();
				fd.shape = shape.get();
				boundBody->CreateFixture(&fd);

				auto objectState = ObjectState::create(boundBody, boundaryObject.mShape, boundaryObject.mColor, boundaryObject.mSize);
				boundBody->SetUserData(objectState.get());

				m_SceneJSONState.add(objectState);
			}
		}

		void AddDynamicObject(b2Vec2 position, b2Vec2 velocity, SimulationObject::Shape shapeType, SimulationObject::Color colorType, SimulationObject::Size sizeType)
		{
			SimulationObject object = SimulationObject(shapeType, colorType, sizeType);

			ShapePtr shape = object.getShape();

			b2BodyDef bd;
			bd.type = b2_dynamicBody;
			bd.position = position;
			bd.angle = RandomFloat(M_PI, M_PI);
			bd.linearVelocity = velocity;
			BODY* body = (BODY*)m_world->CreateBody(&bd);

			b2FixtureDef fd = b2FixtureDef();
			fd.density = object.getDensity();
			fd.restitution = object.getRestitution();
			fd.friction = object.getFriction();
			fd.shape = shape.get();

			//fd.friction = 100.0f; --> TODO: WHAT IS THAT FRICTION
			body->CreateFixture(&fd);

			body->setColor(object.getColor());

			auto objectState = ObjectState::create(body, object.mShape, object.mColor, object.mSize);
			body->SetUserData(objectState.get());

			m_SceneJSONState.add(objectState);
		}

		


		void AddRandomDynamicObject(b2Vec2 position, b2Vec2 velocity, SimulationObject::Shape shape = SimulationObject::STATIC_PLATFORM) {
			SimulationObject::Shape shapeType;

			if (shape == SimulationObject::CUBE) 
				shapeType = SimulationObject::CUBE;
			else if (shape == SimulationObject::CIRCLE)
				shapeType = SimulationObject::CIRCLE;
			else if (shape == SimulationObject::Shape::TRIANGLE)
				shapeType = SimulationObject::TRIANGLE;
			else
				shapeType = SimulationObject::getRandomShape();
		

			SimulationObject::Color colorType = SimulationObject::getRandomColor();
			SimulationObject::Size sizeType = SimulationObject::getRandomSize();

			if (CheckIfObjectIsUnique(shapeType, colorType, sizeType)) {
				AddDynamicObject(position, velocity, shapeType, colorType, sizeType);
			}
			else {
				AddRandomDynamicObject(position, velocity, shapeType);
			}
		}


		bool CheckIfObjectIsUnique(SimulationObject::Shape shapeType, SimulationObject::Color colorType, SimulationObject::Size sizeType) {
			std::vector<int> temp;
			temp.push_back(shapeType);
			temp.push_back(colorType);
			temp.push_back(sizeType);

			if (std::find(scs.begin(), scs.end(), temp) == scs.end()) {
				scs.push_back(temp);
				return true;
			}
			return false;
		}

		void AddStaticObject(b2Vec2 position, float32 angle, SimulationObject::Shape shapeType)
		{
			SimulationObject object = SimulationObject(shapeType, SimulationObject::BLACK, SimulationObject::LARGE);
			ShapePtr shape = object.getShape();
			b2BodyDef bd;
			bd.type = b2_staticBody;
			bd.position = position;
			bd.angle = angle;
			BODY* body = (BODY*)m_world->CreateBody(&bd);

			b2FixtureDef fd = b2FixtureDef();
			fd.density = object.getDensity();
			fd.restitution = object.getRestitution();
			fd.friction = object.getFriction();
			fd.shape = shape.get();
			body->CreateFixture(&fd);

			body->setColor(object.getColor());

			auto objectState = ObjectState::create(body, object.mShape, object.mColor, object.mSize);
			body->SetUserData(objectState.get());

			m_SceneJSONState.add(objectState);
		}

		void DetectStartTouchingEvents()
		{
			for (auto it = m_Contacts.begin(); it != m_Contacts.end(); it++) {
				if (m_StepCount - it->step > COLLISION_DETECTION_STEP_DIFF) {
					//DETECTED StartTouching_Event
					m_pCausalGraph->addEvent(StartTouchingEvent::create(it->step, (BODY*)it->contact->GetFixtureA()->GetBody(),
						(BODY*)it->contact->GetFixtureB()->GetBody()));
					m_StartedTouchingContacts.push_back(*it);
					m_Contacts.erase(it--);
				}
			}
		}

		virtual void BeginContact(b2Contact* contact)  override {
			b2Fixture* fixtureA = contact->GetFixtureA();
			b2Fixture* fixtureB = contact->GetFixtureB();
			bool sensorA = fixtureA->IsSensor();
			bool sensorB = fixtureB->IsSensor();
			b2Fixture* sensorFixture = sensorA ? fixtureA : (sensorB) ? fixtureB : nullptr;
			b2Fixture* otherFixture = sensorA ? fixtureB : (sensorB) ? fixtureA : nullptr;
			if (!sensorFixture) // If no sensor involved in this contact.
			{
				ContactInfo info;
				info.contact = contact;
				info.step = m_StepCount;

				m_Contacts.push_back(info);
			}
			else if (sensorFixture->GetFilterData().categoryBits == SimulationObject::SENSOR_BASKET) {
				// DETECTED ContainerEndUp_Event
				m_pCausalGraph->addEvent(ContainerEndUpEvent::create(m_StepCount,
					(BODY*)sensorFixture->GetBody()->GetUserData(), // The attached body of this sensor body.
					(BODY*)otherFixture->GetBody()));
			}
		}

		virtual void EndContact(b2Contact* contact)  override {
			for (auto it = m_StartedTouchingContacts.begin(); it != m_StartedTouchingContacts.end(); it++) {
				if (it->contact == contact) {
					//DETECTED EndTouching_Event
					m_pCausalGraph->addEvent(EndTouchingEvent::create(m_StepCount, (BODY*)it->contact->GetFixtureA()->GetBody(),
						(BODY*)it->contact->GetFixtureB()->GetBody()));
					m_StartedTouchingContacts.erase(it--);
				}
			}
			for (auto it = m_Contacts.begin(); it != m_Contacts.end(); it++) {
				if (it->contact == contact) {
					//DETECTED Collision_Event
					m_pCausalGraph->addEvent(CollisionEvent::create(it->step, (BODY*)it->contact->GetFixtureA()->GetBody(),
						(BODY*)it->contact->GetFixtureB()->GetBody()));
					m_Contacts.erase(it--);
				}
			}
		}

		void AddSimulationObject(b2Vec2 position, b2Vec2 velocity, SimulationObject::Shape shapeType, SimulationObject::Color colorType, SimulationObject::Size sizeType)
		{
			SimulationObject object = SimulationObject(shapeType, colorType, sizeType);

			ShapePtr shape = object.getShape();

			b2BodyDef bd;
			bd.type = b2_dynamicBody;
			bd.position = position;
			bd.angle = RandomFloat(0.0f, M_PI);
			bd.linearVelocity = velocity;
			BODY* body = (BODY*)m_world->CreateBody(&bd);

			b2FixtureDef fd = b2FixtureDef();
			fd.density = object.getDensity();
			fd.restitution = object.getRestitution();
			fd.friction = object.getFriction();
			fd.shape = shape.get();
			body->CreateFixture(&fd);

			body->setColor(object.getColor());

			auto objectState = ObjectState::create(body, object.mShape, object.mColor, object.mSize);
			body->SetUserData(objectState.get());

			m_SceneJSONState.add(objectState);
		}

		struct ContactInfo
		{
			b2Contact* contact;
			int step;
		};

		std::vector<ContactInfo>    m_Contacts;
		std::vector<ContactInfo>    m_StartedTouchingContacts;

		CausalGraph::Ptr            m_pCausalGraph;
		SceneState                  m_SceneJSONState;

		json						m_StartSceneStateJSON;
		json						m_EndSceneStateJSON;

	};
}

#endif /* SimulationBase_h */
