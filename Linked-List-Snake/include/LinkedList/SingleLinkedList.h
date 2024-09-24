#pragma once

#include "LinkedList/Node.h"
#include "Player/Direction.h"

namespace LinkedList
{
	class SingleLinkedList
	{
	private:
		Node* head_node;
		float node_width;
		float node_height;
		sf::Vector2i default_position;
		Player::Direction default_direction;
	};
}