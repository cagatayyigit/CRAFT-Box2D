//
//  SimulationMaterial.h
//  Testbed
//
//  Created by Tayfun Ateş on 5.10.2019.
//

#ifndef SimulationMaterial_h
#define SimulationMaterial_h

#include <string>
#include "Box2D/Extension/b2VisTexture.hpp"

class SimulationMaterial
{
public:
    enum TYPE
    {
        METAL = 0,
        RUBBER = 1,
    };

    SimulationMaterial(TYPE t)
    {
        type = t;
    }

    float GetDensity()
    {
        if(type == METAL)
        {
            return 10.0F;
        }
        return 5.0F;
    }

    TYPE type;
    
    //Creates the texture associated with the material
    b2VisTexture::Ptr getTexture();
    
private:
    static const std::string filePath;
    static b2VisTexture::Ptr materialTextures;
};

#endif /* SimulationMaterial_h */
