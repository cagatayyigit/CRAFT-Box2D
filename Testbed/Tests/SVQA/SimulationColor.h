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
        BLACK = 8,
        GREEN2 = 9,
        BLUE2 = 10,
        RED2 = 11,
        YELLOW2 = 12
    };

    SimulationColor(TYPE t)
    {
        type = t;
    }

    TYPE type;

    b2Color GetColor()
    {
        switch (type)
        {
            case BLUE: return b2Color(100.0F / 255.0F, 185.0f / 255.0F, 255.0f / 255.0F);
            case BROWN: return b2Color(171.0F / 255.0F, 130.0f / 255.0F, 20.0f / 255.0F);
            case CYAN: return b2Color(68.0F / 255.0F, 195.0f / 255.0F, 193.0f / 255.0F);
            case GRAY: return b2Color(152.0F / 255.0F, 152.0f / 255.0F, 152.0f / 255.0F);
            case GREEN: return b2Color(40.0F / 255.0F, 152.0f / 255.0F, 40.0f / 255.0F);
            case PURPLE: return b2Color(175.0F / 255.0F, 101.0f / 255.0F, 221.0f / 255.0F);
            case RED: return b2Color(152.0F / 255.0F, 40.0f / 255.0F, 40.0f / 255.0F);
            case YELLOW: return b2Color(243.0F / 255.0F, 242.0f / 255.0F, 81.0f / 255.0F);
            case BLACK: return b2Color(0.0F / 255.0F, 0.0f / 255.0F, 0.0f / 255.0F);
            case GREEN2: return b2Color(0.0F, 255.0F, 0.0f);
            case BLUE2: return b2Color(0.0F, 0.0f, 255.0f);
            case RED2: return b2Color(255.0F, 0.0f, 0.0f);
            case YELLOW2: return b2Color(1, 1, 0);

        }
        return b2Color(0.0f, 0.0f, 0.0f, 0.0f);
    }

};

NLOHMANN_JSON_SERIALIZE_ENUM( SimulationColor::TYPE, {
    {SimulationColor::BLUE, "blue"},
    {SimulationColor::BROWN, "brown"},
    {SimulationColor::CYAN, "cyan"},
    {SimulationColor::GRAY, "gray"},
    {SimulationColor::GREEN, "green"},
    {SimulationColor::PURPLE, "purple"},
    {SimulationColor::RED, "red"},
    {SimulationColor::YELLOW, "yellow"},
    {SimulationColor::BLACK, "black"},
    {SimulationColor::GREEN2, "green2"},
    {SimulationColor::BLUE2, "blue2"},
    {SimulationColor::RED2, "red2"},
    {SimulationColor::YELLOW2, "yellow2"}
})

#endif /* SimulationColor_h */
