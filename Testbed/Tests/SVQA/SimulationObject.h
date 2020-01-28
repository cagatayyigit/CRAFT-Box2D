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
#include "Box2D/Collision/Shapes/b2CircleShape.h"
#include "Box2D/Collision/Shapes/b2EdgeShape.h"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Box2D/Collision/Shapes/b2ChainShape.h"

#include "SimulationDefines.h"

typedef std::shared_ptr<b2Shape> ShapePtr;

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
		BIG_HEXAGON = 6,
		WALL_PIN = 7,
		ROPE_UNIT = 8,
		SMALL_CIRCLE = 9,
		BIG_CIRCLE = 10,
		BIG_RAMP = 11,
		CUSTOM_RECTANGLE = 12,
		CAR_BODY = 13,
		CAR_WHEEL = 14,
		ROD_RECTANGLE = 15,
		SQUARE = 16

	};

	SimulationObject(TYPE t)
	{
		type = t;
	}

	ShapePtr getShape()
	{
		switch (type) {
		case SMALL_CUBE:
			return std::make_shared<b2PolygonShape>(getPolygon(2.0f, 4));
		case BIG_CUBE:
			return std::make_shared<b2PolygonShape>(getPolygon(3.0f, 4));
		case STANDARD_RECTANGLE:
			return std::make_shared<b2PolygonShape>(getRectangle(8.0f, 2.0f));
		case SMALL_HEXAGON:
			return std::make_shared<b2PolygonShape>(getPolygon(2.0f, 6));
		case BIG_HEXAGON:
			return std::make_shared<b2PolygonShape>(getPolygon(3.0f, 6));
		case SMALL_TRIANGLE:
			return std::make_shared<b2PolygonShape>(getPolygon(2.0f, 3));
		case BIG_TRIANGLE:
			return std::make_shared<b2PolygonShape>(getPolygon(3.0f, 3));
		case WALL_PIN:
			return std::make_shared<b2PolygonShape>(getPolygon(0.5f, 4));
		case ROPE_UNIT:
			return std::make_shared<b2PolygonShape>(getPolygon(0.1f, 4));
		case SMALL_CIRCLE:
			return std::make_shared<b2CircleShape>(getCircle(2.0f));
		case BIG_CIRCLE:
			return std::make_shared<b2CircleShape>(getCircle(3.0f));
		case BIG_RAMP:
			return std::make_shared<b2PolygonShape>(getPolygon(3.0f, 3));
		case CAR_BODY:
			return std::make_shared<b2PolygonShape>(getCarBodyIrregularPolygon());
		case CAR_WHEEL:
			return std::make_shared<b2CircleShape>(getCircle(1.0f));
		case ROD_RECTANGLE:
			return std::make_shared<b2PolygonShape>(getRectangle(10.0f, 1.0f));
		case SQUARE:
			return std::make_shared<b2PolygonShape>(getRectangle(1.0f, 1.0f));
		default:
			break;
		}
		return nullptr;
	}

	TYPE type;

	static b2VisPolygonShape getCube(const float& edgeLength)
	{
		b2VisPolygonShape shape;
		shape.SetAsBox(edgeLength, edgeLength);
		return shape;
	}

	static b2VisPolygonShape getRectangle(const float& w, const float& h)
	{
		b2VisPolygonShape shape;
		shape.SetAsBox(w, h);
		return shape;
	}

	static b2VisPolygonShape getRectangle(const float& w, const float& h, b2Vec2 center, float32 angle)
	{
		b2VisPolygonShape shape;
		shape.SetAsBox(w, h, center, angle);
		return shape;
	}

	static b2Vec2 rotate(const b2Vec2& v, const float anglesInRadians)
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

	static b2VisPolygonShape getPolygon(const float& edgeLength, const int& nPoints)
	{
		const float twoPi = 2.0f * 3.14159265f;
		std::vector<b2Vec2> points(nPoints);
		points[0] = b2Vec2(0.0f, -edgeLength);
		b2Vec2 currentPoint = points[0];
		const float rotationAngle = twoPi / nPoints;
		for (size_t i = 1; i < points.size(); i++)
		{
			currentPoint = rotate(currentPoint, rotationAngle);
			points[i] = currentPoint;
		}
		b2VisPolygonShape shape;
		shape.Set(points.data(), nPoints);
		return shape;
	}

	static b2CircleShape getCircle(const float& radius)
	{
		b2CircleShape circle;
		circle.m_radius = radius;
		return circle;
	}

	static b2ChainShape getCurve(std::function<float(float)> function, float fromX, float toX, float step)  
	{
		b2ChainShape shape = b2ChainShape();
		std::vector<b2Vec2> vertices = std::vector<b2Vec2>();
		float x = fromX;
		while (x <= toX) 
		{
			vertices.push_back(b2Vec2(x, function(x)));
			x += step;
		}

		shape.CreateChain(vertices.data(), vertices.size());
		return shape;
	}

	static b2VisPolygonShape getRightTriangle(const float& vEdgeLength, const float& hEdgeLength)
	{
		b2VisPolygonShape shape;
		// TODO
		b2Vec2 vertex1 = b2Vec2(vEdgeLength, 0);
		b2Vec2 vertex2 = b2Vec2(0, hEdgeLength);
		b2Vec2 vertex3 = b2Vec2(0, 0);

		std::vector<b2Vec2>  vertices = std::vector<b2Vec2>();
		vertices.push_back(vertex1);
		vertices.push_back(vertex2);
		vertices.push_back(vertex3);

		shape.Set(vertices.data(), 3);
		return shape;
	}

	b2VisPolygonShape getCarBodyIrregularPolygon()
	{
		b2VisPolygonShape chassis;
		b2Vec2 vertices[8];
		const float scale = 3.0;
		vertices[0].Set(scale * -1.5f, scale * -0.5f);
		vertices[1].Set(scale * 1.5f, scale * -0.5f);
		vertices[2].Set(scale * 1.5f, scale * 0.0f);
		vertices[3].Set(scale * 0.0f, scale * 0.9f);
		vertices[4].Set(scale * -1.15f, scale * 0.9f);
		vertices[5].Set(scale * -1.5f, scale * 0.2f);
		chassis.Set(vertices, 6);
		return chassis;
	}
};

NLOHMANN_JSON_SERIALIZE_ENUM(SimulationObject::TYPE, {
	{SimulationObject::SMALL_CUBE, "small_cube"},
	{SimulationObject::BIG_CUBE, "big_cube"},
	{SimulationObject::CUSTOM_RECTANGLE, "custom_rectangle"}
	})

#endif /* SimulationObject_h */
