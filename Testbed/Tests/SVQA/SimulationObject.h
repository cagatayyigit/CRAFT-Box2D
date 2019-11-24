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
        STANDARD_RECTANGLE = 2,
        SMALL_TRIANGLE = 3,
        BIG_TRIANGLE = 4,
        SMALL_HEXAGON = 5,
        BIG_HEXAGON = 6
    };

    SimulationObject(TYPE t)
    {
        type = t;
    }

    b2VisPolygonShape getShape()
    {
        switch (type) {
            case SMALL_CUBE:
                return getPolygon(2.0f, 4);
            case BIG_CUBE:
                return getPolygon(3.0f, 4);
            case STANDARD_RECTANGLE:
                return getRectangle(8.0f, 2.0f);
            case SMALL_HEXAGON:
                return getPolygon(2.0f, 6);
            case BIG_HEXAGON:
                return getPolygon(3.0f, 6);
            case SMALL_TRIANGLE:
                return getPolygon(2.0f, 3);
            case BIG_TRIANGLE:
                return getPolygon(3.0f, 3);
            
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
    
    b2Vec2 rotate(const b2Vec2& v, const float anglesInRadians)
    {
        const float s = sin(anglesInRadians);
        const float c = cos(anglesInRadians);
        b2Vec2 ret = v;
        b2Vec2 translatedPoint = ret;
        translatedPoint.x = ret.x * c - ret.y * s;
        translatedPoint.y = ret.x * s + ret.y * c;
        ret.x = translatedPoint.x;
        ret.y = translatedPoint.y;
        return ret;
    }
    
    b2VisPolygonShape getPolygon(const float& edgeLength, const int& nPoints)
    {
        const float twoPi =  2.0f * 3.14159265f;
        std::vector<b2Vec2> points(nPoints);
        points[0] = b2Vec2(0.0f, -edgeLength);
        b2Vec2 currentPoint = points[0];
        const float rotationAngle = twoPi / nPoints;
        for(size_t i = 1; i < points.size(); i++)
        {
            currentPoint = rotate(currentPoint, rotationAngle);
            points[i] = currentPoint;
        }
        b2VisPolygonShape shape;
        shape.Set(points.data(), nPoints);
        return shape;
    }
    
};

NLOHMANN_JSON_SERIALIZE_ENUM( SimulationObject::TYPE, {
    {SimulationObject::SMALL_CUBE, "small_cube"},
    {SimulationObject::BIG_CUBE, "big_cube"}
})

#endif /* SimulationObject_h */
