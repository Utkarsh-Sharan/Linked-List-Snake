#pragma once
#include <vector>
#include <SFML/System/Vector2.hpp>
#include "Player/PlayerController.h"

namespace Player
{
	class PlayerController;

	class PlayerService
	{
	private:
		PlayerController* player_controller;

		void createController();
		void destroy();

	public:
		PlayerService();
		~PlayerService();

		void initialize();
		void update();
		void render();

		void spawnPlayer();
		std::vector<sf::Vector2i> getCurrentPlayerPositionList();

		int getPlayerSize();
		int getPlayerScore();
		TimeComplexity getTimeComplexity();
		PlayerState getPlayerState();
	};
}