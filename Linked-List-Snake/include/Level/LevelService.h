#pragma once

#include "Level/LevelConfig.h"

namespace Level
{
	class LevelController;

	class LevelService
	{
    private:
        LevelController* level_controller;
        LevelNumber current_level;
        LinkedListType current_linked_list_type;

        void createLevelController();
        void spawnLevelElements(LevelNumber level_to_load);
        void spawnPlayer();
        void spawnFood();
        void destroy();

    public:
        LevelService();
        ~LevelService();

        void initialize();
        void update();
        void render();

        void createLevel(LinkedListType linked_list_type);

        float getCellWidth();
        float getCellHeight();

        LevelNumber getCurrentLevel();
        void setCurrentLevelNumber(LevelNumber level_to_load);
	};
}