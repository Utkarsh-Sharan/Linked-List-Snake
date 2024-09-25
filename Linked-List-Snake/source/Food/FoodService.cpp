#include "Food/FoodService.h"
#include "Global/ServiceLocator.h"
#include "Food/FoodItem.h"
#include "Level/LevelModel.h"
#include "Player/PlayerService.h"

namespace Food
{
	using namespace Time;
	using namespace Global;
	using namespace Level;
	using namespace Player;

	FoodService::FoodService() : random_engine(random_device())
	{
		current_food_item = nullptr;
	}

	FoodService::~FoodService()
	{
		destroyFood();
	}

	void FoodService::initialize()
	{
		//Yet to implement
	}

	void FoodService::startFoodSpawning()
	{
		cell_width = ServiceLocator::getInstance()->getLevelService()->getCellWidth();
		cell_height = ServiceLocator::getInstance()->getLevelService()->getCellHeight();
		spawnFood();
	}

	void FoodService::spawnFood()
	{
		current_food_item = createFood(sf::Vector2i(4, 6), FoodType::BURGER);
	}

	FoodItem* FoodService::createFood(sf::Vector2i position, FoodType type)
	{
		FoodItem* food = new FoodItem();
		food->initialize(position, cell_width, cell_height, type);
		return food;
	}

	void FoodService::update()
	{
		if (current_food_item) 
			current_food_item->update();
	}

	void FoodService::render()
	{
		if (current_food_item) 
			current_food_item->render();
	}

	sf::Vector2i FoodService::getRandomPosition()
	{
		// Coordinate distribution for selecting a random position for food
		std::uniform_int_distribution<int> x_distribution(0, LevelModel::number_of_columns - 1);
		std::uniform_int_distribution<int> y_distribution(0, LevelModel::number_of_rows - 1);

		int x_position = x_distribution(random_engine);
		int y_position = y_distribution(random_engine);

		return sf::Vector2i(x_position, y_position);
	}

	void FoodService::destroyFood()
	{
		if (current_food_item) 
			delete(current_food_item);
	}
}