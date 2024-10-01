#pragma once

#include "LinkedListLib/LinkedList.h"
#include "Player/Direction.h"

#include <SFML/System/Vector2.hpp>

namespace LinkedListLib
{
	namespace SingleLinked
	{
		class SingleLinkedList : public LinkedList
		{
		protected:
			Node* createNode() override;

		public:
			SingleLinkedList();
			~SingleLinkedList();

			//Insertion operation methods
			void insertNodeAtHead() override;
			void insertNodeAtMiddle() override;
			void insertNodeAtTail() override;
			void insertNodeAtIndex(int index);
			void shiftNodesAfterInsertion(Node* new_node, Node* cur_node, Node* prev_node);

			//Removal operation methods
			void removeNodeAtHead() override;
			void removeNodeAtMiddle() override;
			void removeNodeAtTail() override;
			void removeNodeAtIndex(int index) override;
			void removeHalfNodes() override;
			void removeAllNodes() override;
			void shiftNodesAfterRemoval(Node* cur_node);

			Direction reverse() override;
		};
	}
}