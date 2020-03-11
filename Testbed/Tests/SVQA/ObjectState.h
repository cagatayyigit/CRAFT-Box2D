//
//  ObjectState.h
//  Testbed
//
//  Created by Tayfun Ateş on 20.10.2019.
//

#ifndef ObjectState_h
#define ObjectState_h

#include "SimulationMaterial.h"
#include "SimulationColor.h"
#include "SimulationObject.h"
#include "Box2D/Common/b2Math.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include "Box2D/Extension/b2VisBody.hpp"
#include "Box2D/Extension/b2VisWorld.hpp"
#include "SimulationDefines.h"



using json = nlohmann::json;

struct ObjectState
{
public:

	typedef std::shared_ptr<ObjectState> Ptr;

	ObjectState(b2VisBody* body,
		const SimulationMaterial::TYPE& materialType,
		const SimulationColor::TYPE& colorType,
		const SimulationObject::TYPE& objectType) :

		body(body),
		materialType(materialType),
		colorType(colorType),
		objectType(objectType)

	{}

	ObjectState() {
		body = nullptr;
	}

	static Ptr create(b2VisBody* body,
		const SimulationMaterial::TYPE& materialType,
		const SimulationColor::TYPE& colorType,
		const SimulationObject::TYPE& objectType)
	{
		return std::make_shared<ObjectState>(body, materialType, colorType, objectType);
	}

	std::string getShortRepresentation()
	{
		std::string ret = "id: " + std::to_string(body->getUniqueId()) + " sh: " + SimulationObject::getRepresentation(objectType) + " col: " + SimulationColor::getRepresentation(colorType);
		return ret;
	}

	std::string getImagePath()
	{

		std::string type = SimulationObject::getRepresentation(objectType); 
		std::string color = SimulationColor::getRepresentation(colorType);

		//std::string basePath = "\"..\\Testbed\\Data\\Images\\";
        std::string basePath = "\"../Testbed/Data/Images/";

		std::string result = basePath + type + "_" + color  + ".png";

		//return "\"C:\\Users\\Cagatay\\Projects\\SVQA\\SVQA-Box2D\\Testbed\\Data\\Images\\" + type + "_" + color + ".png";
		return result;
	}

	void to_json(json& j) const {
		if (body) {
			j.emplace("active", body->IsActive());
			j.emplace("posX", body->GetPosition().x);
			j.emplace("posY", body->GetPosition().y);
			j.emplace("angle", body->GetAngle());
			j.emplace("linearVelocityX", body->GetLinearVelocity().x);
			j.emplace("linearVelocityY", body->GetLinearVelocity().y);
			j.emplace("angularVelocity", body->GetAngularVelocity());
			j.emplace("linearDamping", body->GetLinearDamping());
			j.emplace("angularDamping", body->GetAngularDamping());
			j.emplace("bodyType", body->GetType());
			j.emplace("uniqueID", body->getUniqueId());

			j.emplace("gravityScale", body->GetGravityScale());
			j.emplace("bullet", body->IsBullet());
			j.emplace("allowSleep", body->IsSleepingAllowed());
			j.emplace("awake", body->IsAwake());
			j.emplace("fixedRotation", body->IsFixedRotation());

			b2MassData massData;
			body->GetMassData(&massData);

			j.emplace("massData-mass", massData.mass);
			j.emplace("massData-centerX", massData.center.x);
			j.emplace("massData-centerY", massData.center.y);
			j.emplace("massData-I", massData.I);
		}

		j.emplace("materialType", materialType);
		j.emplace("colorType", colorType);
		j.emplace("objectType", objectType);
	}

	void from_json(const json& j, WORLD* toWorld) {
		bool active, bullet, allowSleep, awake, fixedRotation;
		float x, y, angle, velx, vely, angVel, linearDamp, angDamp, friction;
		float gravityScale, mass, massCenterX, massCenterY, massInertia;
		int bodyType;

		j.at("active").get_to(active);
		j.at("posX").get_to(x);
		j.at("posY").get_to(y);
		j.at("angle").get_to(angle);
		j.at("linearVelocityX").get_to(velx);
		j.at("linearVelocityY").get_to(vely);
		j.at("angularVelocity").get_to(angVel);
		j.at("linearDamping").get_to(linearDamp);
		j.at("angularDamping").get_to(angDamp);
		j.at("bodyType").get_to(bodyType);
		j.at("materialType").get_to(materialType);
		j.at("colorType").get_to(colorType);
		j.at("objectType").get_to(objectType);

		j.at("gravityScale").get_to(gravityScale);
		j.at("bullet").get_to(bullet);
		j.at("allowSleep").get_to(allowSleep);
		j.at("awake").get_to(awake);
		j.at("fixedRotation").get_to(fixedRotation);

		b2MassData massData;
		j.at("massData-mass").get_to(massData.mass);
		j.at("massData-centerX").get_to(massData.center.x);
		j.at("massData-centerY").get_to(massData.center.y);
		j.at("massData-I").get_to(massData.I);

		ShapePtr shape = SimulationObject(objectType).getShape();

		SimulationMaterial mat = SimulationMaterial(materialType);

		b2BodyDef bd;
		bd.type = (b2BodyType)bodyType;
		bd.position = b2Vec2(x, y);
		bd.angle = angle;
		bd.linearVelocity = b2Vec2(velx, vely);
		bd.angularVelocity = angVel;
		bd.linearDamping = linearDamp;
		bd.angularDamping = angDamp;

		bd.allowSleep = allowSleep;
		bd.awake = awake;
		bd.bullet = bullet;
		bd.fixedRotation = fixedRotation;

		body = (BODY*)toWorld->CreateBody(&bd);

		b2FixtureDef fd = b2FixtureDef();
		fd.friction = mat.getFriction();
		fd.density = mat.getDensity();
		fd.shape = shape.get();

		body->CreateFixture(&fd);
		body->SetActive(active);
		body->SetMassData(&massData);
		body->SetGravityScale(gravityScale);

#if !USE_DEBUG_DRAW
		SimulationColor col = SimulationColor(colorType);
		body->setTexture(mat.getTexture());
		body->setColor(col.GetColor());
#endif

		body->SetUserData(this);
	}

	BODY* body;
	SimulationMaterial::TYPE materialType;
	SimulationColor::TYPE colorType;
	SimulationObject::TYPE objectType;
};



#endif /* ObjectState_h */
