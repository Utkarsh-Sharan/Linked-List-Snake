#pragma once

#include "LinkedListLib/Node.h"

namespace LinkedListLib
{
	namespace DoubleNode
	{
		struct DoubleNode : public Node
		{
			Node* previous = nullptr;
		};
	}
}