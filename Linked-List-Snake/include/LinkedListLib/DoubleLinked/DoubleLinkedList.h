#pragma once

#include "LinkedListLib/LinkedList.h"

namespace LinkedListLib
{
	namespace DoubleLinked
	{
		class DoubleLinkedList : public LinkedList
		{
		protected:
			virtual Node* createNode() override;

		public:
			DoubleLinkedList();
			~DoubleLinkedList();

			//Insertion operation methods
			void insertNodeAtHead() override;
			void insertNodeAtMiddle() override;
			void insertNodeAtTail() override;
			void insertNodeAtIndex(int index) override;
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