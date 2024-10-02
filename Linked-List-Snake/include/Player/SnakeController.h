#pragma once

#include "Player/Direction.h"
#include "Food/FoodType.h"
#include "Level/LevelConfig.h"
#include "LinkedListLib/LinkedList.h"

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

	enum class TimeComplexity
	{
		NONE,
		ONE,
		N,
	};

	enum class LinkedListOperations
	{
		NONE,
		INSERT_AT_HEAD,
		INSERT_AT_TAIL,
		INSERT_AT_MID,
		REMOVE_AT_HEAD,
		REMOVE_AT_TAIL,
		REMOVE_AT_MID,
		DELETE_HALF_LIST,
		REVERSE_LIST,
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

		int player_score;

		Direction current_snake_direction;
		SnakeState current_snake_state;
		InputState input_state;

		TimeComplexity time_complexity;
		LinkedListOperations last_linked_list_operation;

		LinkedListLib::LinkedList* linked_list;

		void initializeLinkedList();

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

		void createLinkedList(Level::LinkedListType linked_list_type);
		void initialize();
		void update();
		void render();

		void spawnSnake();
		void respawnSnake();

		void setSnakeState(SnakeState state);
		SnakeState getSnakeState();

		std::vector<sf::Vector2i> getCurrentSnakePositionList();
		int getPlayerScore();

		TimeComplexity getTimeComplexity();
		LinkedListOperations getLastOperation();
	};
}