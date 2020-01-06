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
		CUSTOM_RECTANGLE = 12
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

	static b2VisPolygonShape getRectangle(const float& w, const float& h, VECTOR center, float32 angle)
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

	static b2VisPolygonShape getRightTriangle(const float& vEdgeLength, const float& hEdgeLength)
	{
		b2VisPolygonShape shape;
		// TODO
		VECTOR vertex1 = VECTOR(vEdgeLength, 0);
		VECTOR vertex2 = VECTOR(0, hEdgeLength);
		VECTOR vertex3 = VECTOR(0, 0);

		std::vector<VECTOR>  vertices = std::vector<VECTOR>();
		vertices.push_back(vertex1);
		vertices.push_back(vertex2);
		vertices.push_back(vertex3);

		shape.Set(vertices.data(), 3);
		return shape;
	}



};

NLOHMANN_JSON_SERIALIZE_ENUM(SimulationObject::TYPE, {
	{SimulationObject::SMALL_CUBE, "small_cube"},
	{SimulationObject::BIG_CUBE, "big_cube"},
	{SimulationObject::CUSTOM_RECTANGLE, "custom_rectangle"}
	})

#endif /* SimulationObject_h */
