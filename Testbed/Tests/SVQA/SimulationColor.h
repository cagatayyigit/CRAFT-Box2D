//
//  SimulationColor.h
//  Testbed
//
//  Created by Tayfun Ateş on 5.10.2019.
//

#ifndef SimulationColor_h
#define SimulationColor_h

#include "SimulationMaterial.h"
#include "Box2D/Common/b2Draw.h"
#include <nlohmann/json.hpp>

class SimulationColor
{
public:
    enum TYPE
    {
        BLUE = 0,
        BROWN = 1,
        CYAN = 2,
        GRAY = 3,
        GREEN = 4,
        PURPLE = 5,
        RED = 6,
        YELLOW = 7,
        BLACK = 8
    };

    SimulationColor(TYPE t)
    {
        type = t;
    }

    TYPE type;
    
    static std::string getRepresentation(TYPE t)
    {
        switch (t)
        {
            case BLUE: return "blue";
            case BROWN: return "brown";
            case CYAN: return "cyan";
            case GRAY: return "gray";
            case GREEN: return "green";
            case PURPLE: return "purple";
            case RED: return "red";
            case YELLOW: return "yellow";
            case BLACK: return "black";
        }
    }

    b2Color GetColor()
    {
        switch (type)
        {
            case BLUE: return b2Color(42.0f / 255.0f, 75.0f / 255.0f, 215.0f / 255.0f);
            case BROWN: return b2Color(129.0f / 255.0f, 74.0f / 255.0f, 25.0f / 255.0f);
            case CYAN: return b2Color(41.0f / 255.0f, 208.0f / 255.0f, 208.0f / 255.0f);
            case GRAY: return b2Color(87.0f / 255.0f, 87.0f / 255.0f, 87.0f / 255.0f);
            case GREEN: return b2Color(29.0f / 255.0f, 105.0f / 255.0f, 20.0f / 255.0f);
            case PURPLE: return b2Color(129.0f / 255.0f, 38.0f / 255.0f, 192.0f / 255.0f);
            case RED: return b2Color(173.0f / 255.0f, 35.0f / 255.0f, 35.0f / 255.0f);
            case YELLOW: return b2Color(255.0f / 255.0f, 238.0f / 255.0f, 51.0f / 255.0f);
            case BLACK: return b2Color(0, 0, 0);
        }
    }
};

NLOHMANN_JSON_SERIALIZE_ENUM( SimulationColor::TYPE, {
    {SimulationColor::BLUE, SimulationColor::getRepresentation(SimulationColor::BLUE)},
    {SimulationColor::BROWN, SimulationColor::getRepresentation(SimulationColor::BROWN)},
    {SimulationColor::CYAN, SimulationColor::getRepresentation(SimulationColor::CYAN)},
    {SimulationColor::GRAY, SimulationColor::getRepresentation(SimulationColor::GRAY)},
    {SimulationColor::GREEN, SimulationColor::getRepresentation(SimulationColor::GREEN)},
    {SimulationColor::PURPLE, SimulationColor::getRepresentation(SimulationColor::PURPLE)},
    {SimulationColor::RED, SimulationColor::getRepresentation(SimulationColor::RED)},
    {SimulationColor::YELLOW, SimulationColor::getRepresentation(SimulationColor::YELLOW)},
    {SimulationColor::BLACK, SimulationColor::getRepresentation(SimulationColor::BLACK)},
})

#endif /* SimulationColor_h */
