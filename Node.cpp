#include "Node.h"

Node::Node(int _index, int _key)
{
	state = UNLABELED;
	parent = NULL;
	children = NULL;
	leftSibling = NULL;
	rightSibling = NULL;
	rank = 0;
	state = UNLABELED;
	index = _index;
	key = _key;
}

Node::Node()
{
	parent = NULL;
	children = NULL;
	leftSibling = NULL;
	rightSibling = NULL;
	rank = 0;
	state = UNLABELED;
}
// add children to the root node.
bool Node::addChild(Node* node)
{
	if (children != NULL)
	{
		children->addSibling(node);
	}
	else
	{
		children = node;
		node->parent = this;
		rank = 1;
	}
	return true;
}

// add sibling to the linked list.
bool Node::addSibling(Node* node)
{
	Node* temp = rightMostSibling();
	if (temp == NULL)
		return false;
	temp->rightSibling = node;
	node->leftSibling = temp;
	node->parent = this->parent;
	node->rightSibling = NULL;

	if (parent)
		parent->rank++;

	return true;
}

// remove node.
bool Node::remove()
{
	if (parent)
	{
		parent->rank--;
		if (leftSibling)
		{
			parent->children = leftSibling;
		}
		else if (rightSibling)
		{
			parent->children = rightSibling;
		}
		else
			parent->children = NULL;
	}
	if (leftSibling)
		leftSibling->rightSibling = rightSibling;
	if (rightSibling)
		rightSibling->leftSibling = leftSibling;

	leftSibling = NULL;
	rightSibling = NULL;
	parent = NULL;
	return true;
}

Node* Node::leftMostSibling()
{
	if (this == NULL)
		return NULL;

	Node* temp = this;
	while (temp->leftSibling)
		temp = temp->leftSibling;
	return temp;
}

Node* Node::rightMostSibling()
{
	if (this == NULL)
		return NULL;

	Node* temp = this;
	while (temp->rightSibling)
		temp = temp->rightSibling;
	return temp;
}