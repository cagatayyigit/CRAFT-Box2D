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
#include <nlohmann/json.hpp>

class SimulationMaterial
{
public:
	enum TYPE
	{
        BOUNDARY = -1,
		METAL = 0,
		RUBBER = 1,
	};

	SimulationMaterial(TYPE t)
	{
		type = t;
	}

	float getDensity()
	{
		if (type == METAL) {
			return 10.0f;
		}
        if(type == RUBBER) {
            return 5.0f;
        }
		return 0.0f;
	}
    
    float getFriction()
    {
        return 0.5f;
    }

	float getRestitution()
	{
		switch (type)
		{
		case METAL:
			return 0.02f;
		case RUBBER:
			return 0.35f;
        case BOUNDARY:
            return 0.0f;
		}
		return 0.0f;
	}

	TYPE type;

	//Creates the texture associated with the material
	b2VisTexture::Ptr getTexture();

private:
	static const std::string metalFilePath;
	static const std::string rubberFilePath;
	static b2VisTexture::Ptr metalTexture;
	static b2VisTexture::Ptr rubberTexture;
};

NLOHMANN_JSON_SERIALIZE_ENUM(SimulationMaterial::TYPE, {
	{SimulationMaterial::METAL, "metal"},
	{SimulationMaterial::RUBBER, "rubber"},
	{SimulationMaterial::BOUNDARY, "boundary"}
	})

#endif /* SimulationMaterial_h */
