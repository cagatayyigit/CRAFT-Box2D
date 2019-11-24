//
//  SimulationObject.h
//  Testbed
//
//  Created by Tayfun Ateş on 9.10.2019.
//

#ifndef SimulationObject_h
#define SimulationObject_h

#include <nlohmann/json.hpp>
#include "Box2D/Extension/b2VisPolygonShape.hpp"

class SimulationObject
{
public:
    enum TYPE
    {
        SMALL_CUBE = 0,
        BIG_CUBE = 1,
        STANDARD_RECTANGLE = 2
    };

    SimulationObject(TYPE t)
    {
        type = t;
    }

    b2VisPolygonShape getShape()
    {
        switch (type) {
            case SMALL_CUBE:
                return getCube(2.0f);
            case BIG_CUBE:
                return getCube(4.0f);
            case STANDARD_RECTANGLE:
                return getRectangle(8.0f, 2.0f);
            
            default:
                break;
        }
    }

    TYPE type;
    
private:
    
    b2VisPolygonShape getCube(const float& edgeLength)
    {
        b2VisPolygonShape shape;
        shape.SetAsBox(edgeLength, edgeLength);
        return shape;
    }
    
    b2VisPolygonShape getRectangle(const float& w, const float& h)
    {
        b2VisPolygonShape shape;
        shape.SetAsBox(w, h);
        return shape;
    }
    
};

NLOHMANN_JSON_SERIALIZE_ENUM( SimulationObject::TYPE, {
    {SimulationObject::SMALL_CUBE, "small_cube"},
    {SimulationObject::BIG_CUBE, "big_cube"}
})

#endif /* SimulationObject_h */
