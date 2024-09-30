#include "LinkedList/SingleLinkedList.h"
#include "Player/BodyPart.h"
#include "Level/LevelView.h"

namespace LinkedList
{
	using namespace Player;

	SingleLinkedList::SingleLinkedList()
	{
		head_node = nullptr;
	}

	SingleLinkedList::~SingleLinkedList() = default;

	void SingleLinkedList::initialize(float width, float height, sf::Vector2i position, Direction direction)
	{
		node_width = width;
		node_height = height;
		default_position = position;
		default_direction = direction;

		linked_list_size = 0;
	}

	void SingleLinkedList::initializeNode(Node* new_node, Node* reference_node, Operation operation)
	{
		if (reference_node == nullptr)
		{
			new_node->body_part.initialize(node_width, node_height, default_position, default_direction);
			return;
		}

		sf::Vector2i position = getNewNodePosition(reference_node, operation);

		new_node->body_part.initialize(node_width, node_height, position, reference_node->body_part.getDirection());
	}

	void SingleLinkedList::render() 
	{ 
		Node* cur_node = head_node;

		// Traverse through the linked list and render each node's body part
		while (cur_node != nullptr)
		{     
			cur_node->body_part.render();
			cur_node = cur_node->next;
		}
	}

	void SingleLinkedList::insertNodeAtHead()
	{
		linked_list_size++;
		Node* new_node = createNode();

		if (head_node == nullptr)
		{
			head_node = new_node;
			initializeNode(new_node, nullptr, Operation::HEAD);
			return;
		}

		initializeNode(new_node, head_node, Operation::HEAD);
		new_node->next = head_node;
		head_node = new_node;
	}

	void SingleLinkedList::insertNodeAtMiddle()
	{
		if (head_node == nullptr) {
			insertNodeAtHead();             // If the list is empty, insert at the head.
			return;
		}

		int midIndex = findMiddleNode();    // Use the existing function to find the middle index
		insertNodeAtIndex(midIndex);        // Use the existing function to insert the node at the found index             
	}

	int SingleLinkedList::findMiddleNode()
	{
		Node* slow = head_node;
		Node* fast = head_node;
		int midIndex = 0;  // This will track the index of the middle node.

		// Move fast pointer at 2x speed and slow pointer at 1x speed.
		while (fast != nullptr && fast->next != nullptr) {
			slow = slow->next;
			fast = fast->next->next;
			midIndex++;
		}

		// Now, slow is at the middle node
		return midIndex;
	}

	void SingleLinkedList::insertNodeAtIndex(int index)
	{
		if (index < 0 || index >= linked_list_size) 
			return;

		if (index == 0)
		{
			insertNodeAtHead();
			return;
		}

		Node* new_node = createNode();

		int current_index = 0;
		Node* cur_node = head_node;
		Node* prev_node = nullptr;

		while (cur_node != nullptr && current_index < index)
		{
			prev_node = cur_node;
			cur_node = cur_node->next;
			current_index++;
		}

		prev_node->next = new_node;
		new_node->next = cur_node;
		initializeNode(new_node, prev_node, Operation::TAIL);
		linked_list_size++;

		shiftNodesAfterInsertion(new_node, cur_node, prev_node);
	}

	void SingleLinkedList::shiftNodesAfterInsertion(Node* new_node, Node* cur_node, Node* prev_node)
	{
		Node* next_node = cur_node;
		cur_node = new_node;

		while (cur_node != nullptr && next_node != nullptr)
		{
			cur_node->body_part.setPosition(next_node->body_part.getPosition());
			cur_node->body_part.setDirection(next_node->body_part.getDirection());

			prev_node = cur_node;
			cur_node = next_node;
			next_node = next_node->next;
		}

		initializeNode(cur_node, prev_node, Operation::TAIL);
	}

	void SingleLinkedList::insertNodeAtTail() 
	{
		linked_list_size++;
		Node* new_node = createNode();
		Node* cur_node = head_node;

		if (cur_node == nullptr)
		{
			head_node = new_node;
			initializeNode(new_node, nullptr, Operation::TAIL);
			return;
		}

		while (cur_node->next != nullptr)
		{
			cur_node = cur_node->next;
		}

		cur_node->next = new_node;
		initializeNode(new_node, cur_node, Operation::TAIL);
	}

	Node* SingleLinkedList::createNode()
	{
		return new Node();
	}

	sf::Vector2i SingleLinkedList::getNewNodePosition(Node* reference_node, Operation operation)
	{
		// Extract direction and position for new node calculation
		Direction reference_direction = reference_node->body_part.getDirection();
		sf::Vector2i reference_position = reference_node->body_part.getPosition();

		// Calculate new position based on reference node's direction
		switch (operation)
		{
		case Operation::HEAD:
			return reference_node->body_part.getNextPosition();

		case Operation::TAIL:
			return reference_node->body_part.getPrevPosition();
		}

		return default_position;
	}

	void SingleLinkedList::updateNodeDirection(Direction direction_to_set)
	{
		Node* cur_node = head_node;

		while (cur_node != nullptr)
		{
			Direction previous_direction = cur_node->body_part.getDirection();
			cur_node->body_part.setDirection(direction_to_set);
			direction_to_set = previous_direction;
			cur_node = cur_node->next;
		}
	}

	void SingleLinkedList::updateNodePosition()
	{
		Node* cur_node = head_node;

		while (cur_node != nullptr)
		{
			cur_node->body_part.updatePosition();
			cur_node = cur_node->next;
		}
	}

	bool SingleLinkedList::processNodeCollision()
	{
		if (head_node == nullptr) return false;

		sf::Vector2i predicted_position = head_node->body_part.getNextPosition();

		Node* cur_node = head_node->next;
		while (cur_node != nullptr)
		{
			if (cur_node->body_part.getNextPosition() == predicted_position) return true;
			cur_node = cur_node->next;
		}

		return false;
	}

	std::vector<sf::Vector2i> SingleLinkedList::getNodesPositionList()
	{
		std::vector<sf::Vector2i> nodes_position_list;

		Node* cur_node = head_node;

		while (cur_node != nullptr)
		{
			nodes_position_list.push_back(cur_node->body_part.getPosition());
			cur_node = cur_node->next;
		}

		return nodes_position_list;
	}

	void SingleLinkedList::removeAllNodes()
	{
		if (head_node == nullptr) return;

		while (head_node != nullptr)
		{
			removeNodeAtHead();
		}
	}

	Node* SingleLinkedList::getHeadNode()
	{
		return head_node;
	}

	void SingleLinkedList::removeNodeAtHead()
	{
		linked_list_size--;

		Node* cur_node = head_node;
		head_node = head_node->next;

		cur_node->next = nullptr;
		delete (cur_node);
	}

	void SingleLinkedList::removeNodeAtMiddle()
	{
		if (head_node == nullptr) {
			removeNodeAtHead();             // If the list is empty, remove at the head.
			return;
		}

		int midIndex = findMiddleNode();    // Use the existing function to find the middle index
		removeNodeAtIndex(midIndex);
	}

	void SingleLinkedList::removeNodeAtIndex(int index)
	{
		if (index < 0 || index >= linked_list_size)
			return;

		if (index == 0)
		{
			removeNodeAtHead();
			return;
		}

		int current_index = 0;
		Node* cur_node = head_node;
		Node* prev_node = nullptr;

		while (cur_node != nullptr && current_index < index)
		{
			prev_node = cur_node;
			cur_node = cur_node->next;
			current_index++;
		}

		prev_node->next = cur_node->next;

		shiftNodesAfterRemoval(cur_node);
		delete(cur_node);
		linked_list_size--;
	}

	void SingleLinkedList::shiftNodesAfterRemoval(Node* cur_node)
	{
		sf::Vector2i prev_node_position = cur_node->body_part.getPosition();
		Direction prev_node_direction = cur_node->body_part.getDirection();

		cur_node = cur_node->next;

		while (cur_node != nullptr)
		{
			sf::Vector2i temp_node_position = cur_node->body_part.getPosition();
			Direction temp_node_direction = cur_node->body_part.getDirection();

			cur_node->body_part.setPosition(prev_node_position);
			cur_node->body_part.setDirection(prev_node_direction);

			cur_node = cur_node->next;

			prev_node_position = temp_node_position;
			prev_node_direction = temp_node_direction;
		}
	}

	void SingleLinkedList::removeNodeAtTail()
	{
		if (head_node == nullptr) 
			return;

		Node* cur_node = head_node;

		if (cur_node->next == nullptr) //If only 1 node present
		{
			removeNodeAtHead();
			return;
		}

		while (cur_node->next->next != nullptr)
		{
			cur_node = cur_node->next;
		}

		delete (cur_node->next);
		cur_node->next = nullptr;

		linked_list_size--;
	}

	void SingleLinkedList::removeHalfNodes()
	{
		if (linked_list_size <= 1) 
			return;

		int half_length = linked_list_size / 2;
		int new_tail_index = half_length - 1;

		Node* prev_node = findNodeAtIndex(new_tail_index);
		Node* cur_node = prev_node->next;

		while (cur_node != nullptr)
		{
			Node* node_to_delete = cur_node;
			cur_node = cur_node->next;

			delete (node_to_delete);
			linked_list_size--;
		}

		prev_node->next = nullptr;
	}

	Node* SingleLinkedList::findNodeAtIndex(int index)
	{
		int current_index = 0;
		Node* cur_node = head_node;
		Node* prev_node = nullptr;

		while (cur_node != nullptr && current_index <= index)
		{
			prev_node = cur_node;
			cur_node = cur_node->next;
			current_index++;
		}

		return prev_node;
	}

	Direction SingleLinkedList::reverse()
	{
		Node* cur_node = head_node;
		Node* prev_node = nullptr;
		Node* next_node = nullptr;

		while (cur_node != nullptr)
		{
			next_node = cur_node->next;
			cur_node->next = prev_node;

			prev_node = cur_node;
			cur_node = next_node;
		}

		head_node = prev_node;

		reverseNodeDirections();
		return head_node->body_part.getDirection();
	}

	void SingleLinkedList::reverseNodeDirections()
	{
		Node* curr_node = head_node;

		while (curr_node != nullptr)
		{
			curr_node->body_part.setDirection(getReverseDirection(curr_node->body_part.getPreviousDirection()));
			curr_node = curr_node->next;
		}
	}

	Direction SingleLinkedList::getReverseDirection(Direction direction)
	{
		switch (direction)
		{
		case Direction::UP:
			return Direction::DOWN;

		case Direction::DOWN:
			return Direction::UP;

		case Direction::LEFT:
			return Direction::RIGHT;

		case Direction::RIGHT:
			return Direction::LEFT;
		}
	}
}