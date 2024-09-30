#include "Player/SnakeController.h"
#include "Element/ElementService.h"
#include "Global/ServiceLocator.h"

namespace Player
{
	using namespace LinkedList;
	using namespace Global;
	using namespace Event;
	using namespace Sound;
	using namespace Element;
	using namespace Food;

	SnakeController::SnakeController()
	{
		single_linked_list = nullptr;

		createLinkedList();
	}

	SnakeController::~SnakeController()
	{
		destroy();
	}

	void SnakeController::createLinkedList()
	{
		single_linked_list = new SingleLinkedList();
	}

	void SnakeController::initialize()
	{
		float width = ServiceLocator::getInstance()->getLevelService()->getCellWidth();
		float height = ServiceLocator::getInstance()->getLevelService()->getCellHeight();

		single_linked_list->initialize(width, height, default_position, default_direction);
		reset();
	}

	void SnakeController::update()
	{
		switch (current_snake_state)
		{
		case SnakeState::ALIVE:
			processPlayerInput();
			delayedUpdate();
			break;

		case SnakeState::DEAD:
			handleRestart();
			break;
		}
	}

	void SnakeController::processPlayerInput() 
	{ 
		if (input_state == InputState::PROCESSING) 
			return;

		EventService* event_service = ServiceLocator::getInstance()->getEventService();

		if (event_service->pressedUpArrowKey() && current_snake_direction != Direction::DOWN)
		{
			current_snake_direction = Direction::UP;
			input_state = InputState::PROCESSING;
		}
		else if (event_service->pressedDownArrowKey() && current_snake_direction != Direction::UP)
		{
			current_snake_direction = Direction::DOWN;
			input_state = InputState::PROCESSING;
		}
		else if (event_service->pressedLeftArrowKey() && current_snake_direction != Direction::RIGHT)
		{
			current_snake_direction = Direction::LEFT;
			input_state = InputState::PROCESSING;
		}
		else if (event_service->pressedRightArrowKey() && current_snake_direction != Direction::LEFT)
		{
			current_snake_direction = Direction::RIGHT;
			input_state = InputState::PROCESSING;
		}
	}

	void SnakeController::delayedUpdate()
	{
		elapsed_duration += ServiceLocator::getInstance()->getTimeService()->getDeltaTime();

		if (elapsed_duration >= movement_frame_duration)
		{
			elapsed_duration = 0.f;
			updateSnakeDirection();
			processSnakeCollision();

			if (current_snake_state == SnakeState::ALIVE)
			{
				moveSnake();
				input_state = InputState::WAITING;
			}
		}
	}

	void SnakeController::updateSnakeDirection() 
	{ 
		single_linked_list->updateNodeDirection(current_snake_direction);
	}

	void SnakeController::moveSnake() 
	{ 
		single_linked_list->updateNodePosition();
	}

	void SnakeController::processSnakeCollision() 
	{ 
		processBodyCollision();
		processElementsCollision();
		processFoodCollision();
	}

	void SnakeController::processBodyCollision()
	{
		if (single_linked_list->processNodeCollision())
		{
			current_snake_state = SnakeState::DEAD;
			ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::DEATH);
		}
	}

	void SnakeController::processElementsCollision()
	{
		ElementService* element_service = ServiceLocator::getInstance()->getElementService();

		if (element_service->processElementsCollision(single_linked_list->getHeadNode()))
		{
			current_snake_state = SnakeState::DEAD;
			ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::DEATH);
		}
	}

	void SnakeController::processFoodCollision()
	{
		FoodService* food_service = ServiceLocator::getInstance()->getFoodService();
		FoodType food_type;

		if (food_service->processFoodCollision(single_linked_list->getHeadNode(), food_type))
		{
			ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::PICKUP);

			food_service->destroyFood();
			OnFoodCollected(food_type);
			player_score++;
		}
	}

	void SnakeController::OnFoodCollected(FoodType food_type)
	{
		switch (food_type)
		{
		case FoodType::PIZZA:
			single_linked_list->insertNodeAtTail();
			break;

		case FoodType::BURGER:
			single_linked_list->insertNodeAtHead();
			break;

		case FoodType::CHEESE:
			single_linked_list->insertNodeAtMiddle();
			break;

		case FoodType::APPLE:
			single_linked_list->removeNodeAtHead();
			break;

		case FoodType::MANGO:
			single_linked_list->removeNodeAtMiddle();
			break;

		case FoodType::ORANGE:
			single_linked_list->removeNodeAtTail();
			break;

		case FoodType::POISION:
			single_linked_list->removeHalfNodes();
			break;

		case FoodType::ALCOHOL:
			current_snake_direction = single_linked_list->reverse();
			break;
		}
	}

	void SnakeController::handleRestart()
	{ 
		restart_counter += ServiceLocator::getInstance()->getTimeService()->getDeltaTime();

		if (restart_counter >= restart_duration) 
		{
			respawnSnake();
		}
	}

	void SnakeController::render()
	{
		single_linked_list->render();
	}

	void SnakeController::spawnSnake() 
	{ 
		for (int i = 0; i < initial_snake_length; i++) 
		{
			single_linked_list->insertNodeAtTail();     // Insert nodes at tail to create the initial snake
		}
	}

	void SnakeController::respawnSnake()
	{
		single_linked_list->removeAllNodes();
		reset();
		spawnSnake();
	}

	void SnakeController::setSnakeState(SnakeState state)
	{
		current_snake_state = state;
	}

	SnakeState SnakeController::getSnakeState()
	{
		return current_snake_state;
	}

	std::vector<sf::Vector2i> SnakeController::getCurrentSnakePositionList()
	{
		return single_linked_list->getNodesPositionList();
	}

	int SnakeController::getPlayerScore()
	{
		return player_score;
	}

	void SnakeController::reset()
	{
		current_snake_state = SnakeState::ALIVE;
		current_snake_direction = default_direction;
		elapsed_duration = 0.f;
		restart_counter = 0.f;
		input_state = InputState::WAITING;
		player_score = 0;
	}

	void SnakeController::destroy()
	{
		single_linked_list = nullptr;

		delete(single_linked_list);
	}
}