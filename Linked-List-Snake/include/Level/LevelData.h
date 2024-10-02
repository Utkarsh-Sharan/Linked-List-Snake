#pragma once

#include "Level/LevelConfig.h"
#include "Element/ElementData.h"

#include <vector>
#include <SFML/System/Vector2.hpp>

namespace Level
{
    struct LevelData
    {
        LevelData(LevelNumber ind, std::vector<Element::ElementData>* data_list)
        {
            level_index = ind;
            element_data_list = data_list;
        }

        LevelNumber level_index;
        std::vector<Element::ElementData>* element_data_list;
    };
}