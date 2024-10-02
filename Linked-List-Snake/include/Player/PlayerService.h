#pragma once

#include "Player/SnakeController.h"
#include "Level/LevelConfig.h"
#include <SFML/System/Vector2.hpp>
#include <vector>

namespace Player
{
	class PlayerService
	{
	private:
		SnakeController* snake_controller;

		void createController();

	public:
		PlayerService();
		~PlayerService();

		void initialize();
		void update();
		void render();

		void spawnPlayer(Level::LinkedListType linked_list_type);
		std::vector<sf::Vector2i> getCurrentSnakePositionList();

		bool isPlayerDead();

		int getPlayerScore();

		TimeComplexity getTimeComplexity();
		LinkedListOperations getLastOperation();
	};
}