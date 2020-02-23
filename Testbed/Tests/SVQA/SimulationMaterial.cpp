//
//  SimulationMaterial.cpp
//  Testbed
//
//  Created by Tayfun Ateş on 6.10.2019.
//

#include "SimulationMaterial.h"

const std::string SimulationMaterial::metalFilePath = "Data/Textures/metal.png";
const std::string SimulationMaterial::rubberFilePath = "Data/Textures/rubber.png";
b2VisTexture::Ptr SimulationMaterial::metalTexture;
b2VisTexture::Ptr SimulationMaterial::rubberTexture;

b2VisTexture::Ptr SimulationMaterial::getTexture()
{
    if(type != BOUNDARY) {
        if(!SimulationMaterial::metalTexture) {
            SimulationMaterial::metalTexture = b2VisTexture::Ptr(new b2VisTexture(SimulationMaterial::metalFilePath, SimulationMaterial::METAL));
        }
        
        if(!SimulationMaterial::rubberTexture) {
            SimulationMaterial::rubberTexture = b2VisTexture::Ptr(new b2VisTexture(SimulationMaterial::rubberFilePath, SimulationMaterial::RUBBER));
        }
        
        if(type == METAL) {
            return SimulationMaterial::metalTexture;
        }
        return SimulationMaterial::rubberTexture;
    }
    return nullptr;
}

