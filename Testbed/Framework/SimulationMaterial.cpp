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
    
    if(type == METAL) {
        return b2VisTexture::Ptr(new b2VisTexture(SimulationMaterial::materialTextures->getTextureId(),
                            SimulationMaterial::materialTextures->getAtlasWidth(),
                            SimulationMaterial::materialTextures->getAtlasHeight(),
                            b2Vec2(0.0f, 0.0f),
                            b2Vec2(15.0f, 15.0f)));
    }
    
    return b2VisTexture::Ptr(new b2VisTexture(SimulationMaterial::materialTextures->getTextureId(),
                        SimulationMaterial::materialTextures->getAtlasWidth(),
                        SimulationMaterial::materialTextures->getAtlasHeight(),
                        b2Vec2(0.0f, 16.0f),
                        b2Vec2(15.0f, 31.0f)));
    
}

