//
//  SimulationMaterial.cpp
//  Testbed
//
//  Created by Tayfun Ateş on 6.10.2019.
//

#include "SimulationMaterial.h"

const std::string SimulationMaterial::filePath = "Data/Textures/terrain.png";
b2VisTexture::Ptr SimulationMaterial::materialTextures;

b2VisTexture::Ptr SimulationMaterial::getTexture()
{
    if(!SimulationMaterial::materialTextures) {
        SimulationMaterial::materialTextures = b2VisTexture::Ptr(new b2VisTexture(SimulationMaterial::filePath));
    }
    return SimulationMaterial::materialTextures;
}

