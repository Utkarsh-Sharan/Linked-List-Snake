#pragma once

#include "Player/Direction.h"
#include "Food/FoodType.h"
#include "LinkedList/SingleLinkedList.h"

#include <SFML/Graphics.hpp>

namespace Player
{
	enum class SnakeState
	{
		ALIVE,
		DEAD,
	};

	enum class InputState
	{
		WAITING,
		PROCESSING
	};

	class SnakeController
	{
	private:
		const int initial_snake_length = 10;

		const float movement_frame_duration = 0.1f;
		float elapsed_duration = 0.f;

		const float restart_duration = 2.f;
		float restart_counter = 0.f;

		const sf::Vector2i default_position = sf::Vector2i(25, 13);
		const Direction default_direction = Direction::RIGHT;

		Direction current_snake_direction;
		SnakeState current_snake_state;
		InputState input_state;

		LinkedList::SingleLinkedList* single_linked_list;

		void createLinkedList();

		void processPlayerInput();
		void delayedUpdate();
		void updateSnakeDirection();
		void moveSnake();

		void processSnakeCollision();
		void processBodyCollision();
		void processElementsCollision();
		void processFoodCollision();
		void OnFoodCollected(Food::FoodType food_type);

		void handleRestart();
		void reset();
		void destroy();

	public:
		SnakeController();
		~SnakeController();

		void initialize();
		void update();
		void render();

		void spawnSnake();
		void respawnSnake();

		void setSnakeState(SnakeState state);
		SnakeState getSnakeState();

		std::vector<sf::Vector2i> getCurrentSnakePositionList();
	};
}