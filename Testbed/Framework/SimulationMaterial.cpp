//
//  SimulationMaterial.cpp
//  Testbed
//
//  Created by Tayfun Ateş on 6.10.2019.
//

#include "SimulationMaterial.h"

const std::string SimulationMaterial::metalFilePath = "Data/Textures/metal.png";
const std::string SimulationMaterial::rubberFilePath = "Data/Textures/rubber.png";
const std::string SimulationMaterial::eyesFilePath = "Data/Textures/eyes.jpg";
b2VisTexture::Ptr SimulationMaterial::metalTexture;
b2VisTexture::Ptr SimulationMaterial::rubberTexture;
b2VisTexture::Ptr SimulationMaterial::eyesTexture;

b2VisTexture::Ptr SimulationMaterial::getTexture()
{
    if (!SimulationMaterial::metalTexture) {
        SimulationMaterial::metalTexture = b2VisTexture::Ptr(new b2VisTexture(SimulationMaterial::metalFilePath, SimulationMaterial::METAL));
    }

    if (!SimulationMaterial::rubberTexture) {
        SimulationMaterial::rubberTexture = b2VisTexture::Ptr(new b2VisTexture(SimulationMaterial::rubberFilePath, SimulationMaterial::RUBBER));
    }

    if (!SimulationMaterial::eyesTexture) {
        SimulationMaterial::eyesTexture = b2VisTexture::Ptr(new b2VisTexture(SimulationMaterial::eyesFilePath, SimulationMaterial::EYES));
    }

    if (type == METAL) {
        return SimulationMaterial::metalTexture;
    }

    if (type == EYES) {
        return SimulationMaterial::eyesTexture;
    }

    return SimulationMaterial::rubberTexture;
}
