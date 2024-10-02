#include "Player/PlayerService.h"
#include "Player/SnakeController.h"

namespace Player
{
	using namespace Level;

	PlayerService::PlayerService()
	{
		createController();
	}

	PlayerService::~PlayerService()
	{
		snake_controller = nullptr;

		delete(snake_controller);
	}

	void PlayerService::createController()
	{
		snake_controller = new SnakeController();
	}

	void PlayerService::initialize()
	{
		snake_controller->initialize();
	}

	void PlayerService::update()
	{
		snake_controller->update();
	}

	void PlayerService::render()
	{
		snake_controller->render();
	}

	void PlayerService::spawnPlayer(LinkedListType linked_list_type)
	{
		snake_controller->createLinkedList(linked_list_type);
		snake_controller->spawnSnake();
	}

	int PlayerService::getPlayerScore()
	{
		return snake_controller->getPlayerScore();
	}

	TimeComplexity PlayerService::getTimeComplexity()
	{
		return snake_controller->getTimeComplexity();
	}

	LinkedListOperations PlayerService::getLastOperation()
	{
		return snake_controller->getLastOperation();
	}

	std::vector<sf::Vector2i> PlayerService::getCurrentSnakePositionList()
	{
		return snake_controller->getCurrentSnakePositionList();
	}
}