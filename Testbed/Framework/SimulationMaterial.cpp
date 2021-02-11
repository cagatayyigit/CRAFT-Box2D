//
//  SimulationMaterial.cpp
//  Testbed
//
//  Created by Tayfun Ateş on 6.10.2019.
//

#include "SimulationMaterial.h"

// const std::string SimulationMaterial::metalFilePath = "Data/Textures/metal.png";
// const std::string SimulationMaterial::rubberFilePath = "Data/Textures/rubber.png";
const std::string SimulationMaterial::eyesFilePath = "Data/Textures/eyes.png";
const std::string SimulationMaterial::platformFilePath = "Data/Textures/platform.png";
const std::string SimulationMaterial::sensorFilePath = "Data/Textures/sensor.png";
// b2VisTexture::Ptr SimulationMaterial::metalTexture;
// b2VisTexture::Ptr SimulationMaterial::rubberTexture;
b2VisTexture::Ptr SimulationMaterial::eyesTexture;
b2VisTexture::Ptr SimulationMaterial::platformTexture;
b2VisTexture::Ptr SimulationMaterial::sensorTexture;

b2VisTexture::Ptr SimulationMaterial::getTexture()
{
    //if (!SimulationMaterial::metalTexture) {
    //    SimulationMaterial::metalTexture = b2VisTexture::Ptr(new b2VisTexture(SimulationMaterial::metalFilePath, SimulationMaterial::METAL));
    //}
    //
    //if (!SimulationMaterial::rubberTexture) {
    //    SimulationMaterial::rubberTexture = b2VisTexture::Ptr(new b2VisTexture(SimulationMaterial::rubberFilePath, SimulationMaterial::RUBBER));
    //}
    if (!SimulationMaterial::platformTexture) {
        SimulationMaterial::platformTexture = b2VisTexture::Ptr(new b2VisTexture(SimulationMaterial::platformFilePath, SimulationMaterial::TYPE::PLATFORM));
    }

    if (!SimulationMaterial::sensorTexture) {
        SimulationMaterial::sensorTexture = b2VisTexture::Ptr(new b2VisTexture(SimulationMaterial::sensorFilePath, SimulationMaterial::TYPE::SENSOR));
    }

    if (!SimulationMaterial::eyesTexture) {
        SimulationMaterial::eyesTexture = b2VisTexture::Ptr(new b2VisTexture(SimulationMaterial::eyesFilePath, SimulationMaterial::TYPE::EYES));
    }

    //if (type == METAL) {
    //    return SimulationMaterial::metalTexture;
    //}

    if (type == EYES) {
        return SimulationMaterial::eyesTexture;
    }

    if (type == PLATFORM) {
        return SimulationMaterial::platformTexture;
    }
    
    if (type == SENSOR) {
        return SimulationMaterial::sensorTexture;
    }

    return nullptr;
}
