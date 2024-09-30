#pragma once

#include "Player/SnakeController.h"
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

		void spawnPlayer();
		std::vector<sf::Vector2i> getCurrentSnakePositionList();

		int getPlayerScore();

		TimeComplexity getTimeComplexity();
		LinkedListOperations getLastOperation();
	};
}