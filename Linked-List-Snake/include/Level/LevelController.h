#pragma once

#include "Level/LevelModel.h"

namespace Level
{
	class LevelView;

	class LevelController
	{
	private:
		LevelModel* level_model;
		LevelView* level_view;

		void destroy();

	public:
		LevelController();
		~LevelController();

		void initialize();
		void update();
		void render();

		float getCellWidth();
		float getCellHeight();
	};
}