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

enum Mati
{
    METAL = 0,
    RUBBER = 1,
};

NLOHMANN_JSON_SERIALIZE_ENUM( Mati, {
    {METAL, "metal"},
    {RUBBER, "rubber"}
})

struct ObjectState
{
    ObjectState(b2VisBody* body,
                const SimulationMaterial& materialType,
                const SimulationColor& colorType,
                const SimulationObject& objectType) :
    
                body(body),
                materialType(materialType),
                colorType(colorType),
                objectType(objectType)
    
    {}
    
    void to_json(json& j) {
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
        
        j.emplace("materialType", materialType.type);
        j.emplace("colorType", colorType.type);
        j.emplace("objectType", objectType.type);
    }
    
   

//    void from_json(const json& j) {
//        j.at("simulationID").get_to(this->simulationID);
//        j.at("camWidth").get_to(this->camWidth);
//        j.at("camHeight").get_to(this->camHeight);
//        j.at("scenePath").get_to(this->scenePath);
//    }
    
    b2VisBody* body;
    SimulationMaterial materialType;
    SimulationColor colorType;
    SimulationObject objectType;
};



#endif /* ObjectState_h */
