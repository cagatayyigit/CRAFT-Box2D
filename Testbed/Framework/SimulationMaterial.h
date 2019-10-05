//
//  SimulationMaterial.h
//  Testbed
//
//  Created by Tayfun Ateş on 5.10.2019.
//

#ifndef SimulationMaterial_h
#define SimulationMaterial_h

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
};

#endif /* SimulationMaterial_h */
