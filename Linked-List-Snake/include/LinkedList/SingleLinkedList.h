#pragma once

#include "LinkedList/Node.h"
#include "Player/Direction.h"

#include <SFML/System/Vector2.hpp>

namespace LinkedList
{
	enum class Operation
	{
		HEAD,
		MID,
		TAIL
	};

	class SingleLinkedList
	{
	private:
		int linked_list_size;

		Node* head_node;

		float node_width;
		float node_height;

		sf::Vector2i default_position;
		Player::Direction default_direction;

		Node* createNode();

		void shiftNodesAfterInsertion(Node* new_node, Node* cur_node, Node* prev_node);
		void shiftNodesAfterRemoval(Node* cur_node);

		int findMiddleNode();
		Node* findNodeAtIndex(int index);

	public:
		SingleLinkedList();
		~SingleLinkedList();

		void initialize(float width, float height, sf::Vector2i position, Player::Direction direction);
		void initializeNode(Node* new_node, Node* reference_node, Operation operation);

		void render();

		//Insertion operation methods
		void insertNodeAtHead();
		void insertNodeAtMiddle();
		void insertNodeAtIndex(int index);
		void insertNodeAtTail();

		//Removal operation methods
		void removeNodeAtHead();
		void removeNodeAtMiddle();
		void removeNodeAtIndex(int index);
		void removeNodeAtTail();
		void removeHalfNodes();

		sf::Vector2i getNewNodePosition(Node* reference_node, Operation operation);

		void updateNodeDirection(Direction direction_to_set);
		void updateNodePosition();

		std::vector<sf::Vector2i> getNodesPositionList();
		Node* getHeadNode();

		bool processNodeCollision();
		void removeAllNodes();
	};
}