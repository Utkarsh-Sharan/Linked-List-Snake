#include "LinkedListLib/SingleLinked/SingleLinkedList.h"
#include "LinkedListLib/SingleLinked/SingleNode.h"
#include "Player/BodyPart.h"
#include "Level/LevelView.h"

namespace LinkedListLib
{
	namespace SingleLinked
	{
		using namespace Player;

		SingleLinkedList::SingleLinkedList() = default;

		SingleLinkedList::~SingleLinkedList() = default;

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
			return new SingleNode();
		}

		void SingleLinkedList::removeAllNodes()
		{
			if (head_node == nullptr) 
				return;

			while (head_node != nullptr)
			{
				removeNodeAtHead();
			}
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
			if (head_node == nullptr) 
			{
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
	}
}