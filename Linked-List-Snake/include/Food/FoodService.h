#pragma once
#include <SFML/System/Vector2.hpp>
#include <random>
#include <vector>

namespace Food
{
	enum class FoodType;
	class FoodItem;

	class FoodService
	{
	private:
		FoodItem* current_food_item;

		std::default_random_engine random_engine;
		std::random_device random_device;

		float cell_width;
		float cell_height;

		FoodItem* createFood(sf::Vector2i position, FoodType type);
		void spawnFood();

		void destroyFood();

	public:
		FoodService();
		~FoodService();

		void initialize();
		void update();
		void render();

		void startFoodSpawning();
		sf::Vector2i getRandomPosition();
	};
}