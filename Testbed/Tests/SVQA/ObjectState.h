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
#include "Box2D/Extension/b2VisBody.hpp"
#include "Box2D/Extension/b2VisWorld.hpp"
#include "SimulationDefines.h"

using json = nlohmann::json;

struct ObjectState
{
    friend class SceneState;
    
public:
    
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
    
    typedef std::shared_ptr<ObjectState> Ptr;
    
    static Ptr create(b2VisBody* body,
                      const SimulationMaterial::TYPE& materialType,
                      const SimulationColor::TYPE& colorType,
                      const SimulationObject::TYPE& objectType)
    {
        return std::make_shared<ObjectState>(body, materialType, colorType, objectType);
    }
    
    void to_json(json& j) const {
        if(body) {
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
        }
        
        j.emplace("materialType", materialType);
        j.emplace("colorType", colorType);
        j.emplace("objectType", objectType);
    }
    
    void from_json(const json& j, WORLD* toWorld) {
        bool active;
        float x, y, angle, velx, vely, angVel, linearDamp, angDamp;
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
            
        ShapePtr shape = SimulationObject(objectType).getShape();
        
        SimulationMaterial mat = SimulationMaterial(materialType);
        
        b2BodyDef bd;
        bd.type = (b2BodyType) bodyType;
        bd.position = b2Vec2(x, y);
        bd.angle = angle;
        bd.linearVelocity = b2Vec2(velx, vely);
        bd.angularVelocity = angVel;
        bd.linearDamping = linearDamp;
        bd.angularDamping = angDamp;
        
        body = (BODY*) toWorld->CreateBody(&bd);
        body->CreateFixture(shape.get(), mat.getDensity());
        body->SetActive(active);
        
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
