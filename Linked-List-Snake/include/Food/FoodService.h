#pragma once

#include "LinkedListLib/Node.h"
#include <SFML/System/Vector2.hpp>
#include <random>
#include <vector>

namespace Food
{
	enum class FoodType;
	class FoodItem;

	enum FoodSpawningStatus
	{
		ACTIVE,
		IN_ACTIVE,
	};

	class FoodService
	{
	private:
		const float spawn_duration = 4.f;
		float elapsed_duration;

		FoodSpawningStatus current_spawning_status;
		FoodItem* current_food_item;

		std::default_random_engine random_engine;
		std::random_device random_device;

		float cell_width;
		float cell_height;

		FoodItem* createFood(sf::Vector2i position, FoodType type);
		void spawnFood();

		sf::Vector2i getRandomPosition();
		FoodType getRandomFoodType();
		sf::Vector2i getValidSpawnPosition();

		bool isValidPosition(std::vector<sf::Vector2i> position_data, sf::Vector2i food_position);

		void updateElapsedDuration();
		void handleFoodSpawning();
		void reset();

	public:
		FoodService();
		~FoodService();

		void initialize();
		void update();
		void render();

		void startFoodSpawning();
		void stopFoodSpawning();

		bool processFoodCollision(LinkedListLib::Node* head_node, FoodType& out_food_type);
		void destroyFood();
	};
}