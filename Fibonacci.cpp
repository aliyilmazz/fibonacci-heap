#include "Fibonacci.h"

FibonacciHeap::FibonacciHeap()
{
	rootListByRank = new Node*[1024];
	minRoot = NULL;
}

FibonacciHeap::FibonacciHeap(Node* root)
{
	rootListByRank = new Node*[1024];
	minRoot = root;
}

FibonacciHeap::~FibonacciHeap()
{
	delete[] rootListByRank;
}

bool FibonacciHeap::isEmpty()
{
	return minRoot == NULL;
}

// add node into heap.
bool FibonacciHeap::insertVertex(Node* node)
{
	if (node == NULL)
		return false;
	if (minRoot == NULL)
		minRoot = node;
	else
	{
		minRoot->addSibling(node);
		if (minRoot->key > node->key)
			minRoot = node;
	}
	return true;
}

void FibonacciHeap::decreaseKey(int newKey, Node* vertex)
{
	vertex->key = newKey;
	if (vertex->parent != NULL)
	{
		// remove vertex and add to root list.
		vertex->remove();
		minRoot->addSibling(vertex);
	}
	// check if key is smaller than the key of minRoot
	if (vertex->key < minRoot->key)
		minRoot = vertex;
}

Node* FibonacciHeap::findMin()
{
	return minRoot;
}

// nodes with same child number are merged, two by two.
// each step, the bigger node happens to be the child of smaller node.
bool FibonacciHeap::link(Node* root)
{
	// insert Vertex into root list.
	if (rootListByRank[root->rank] == NULL)
	{
		rootListByRank[root->rank] = root;
		return false;
	}
	else
	{
		Node* linkVertex = rootListByRank[root->rank];
		rootListByRank[root->rank] = NULL;
		if (root->key < linkVertex->key || root == minRoot)
		{
			linkVertex->remove();
			root->addChild(linkVertex);
			if (rootListByRank[root->rank] != NULL)
			{
				link(root);
			}
			else
			{
				rootListByRank[root->rank] = root;
			}
		}
		else
		{
			root->remove();
			linkVertex->addChild(root);
			if (rootListByRank[linkVertex->rank] != NULL)
				link(linkVertex);
			else
				rootListByRank[linkVertex->rank] = linkVertex;

		}
		return true;
	}
}


// deletemin
// copies all children of the node referenced by the access pointer
// into the root list. after each insertion, a linking step is done
// if necessary. at least the minimum element is deleted, and the node
// with the minimum key is determined. the amortized time depends on the
// count of children of the minimum node. in the worst case, for each child,
// a removing, inserting, and linking operation is required. it's O(NlogN).
Node* FibonacciHeap::deleteMin()
{
	Node* temp = minRoot->children->leftMostSibling();
	Node* nextTemp = NULL;

	// adding children to root list.
	while (temp != NULL)
	{
		nextTemp = temp->rightSibling; // save rest of the children.
		temp->remove();
		minRoot->addSibling(temp);
		temp = nextTemp;
	}

	// select the left-most sibling of minRoot
	temp = minRoot->leftMostSibling();

	// remove minRoot and set it to any sibling, if there exists one
	if (temp == minRoot)
	{
		if (minRoot->rightSibling)
			temp = minRoot->rightSibling;
		else
		{
			// heap is obviously empty
			Node* out = minRoot;
			minRoot->remove();
			minRoot = NULL;
			return out;
		}
	}
	Node* out = minRoot;
	minRoot->remove();
	minRoot = temp;

	// initialize list of roots.
	for (int i = 0; i < 1024; i++)
		rootListByRank[i] = NULL;

	while (temp)
	{
		// check if key of current vertex is smaller than the key of minRoot
		if (temp->key < minRoot->key)
			minRoot = temp;
		nextTemp = temp->rightSibling;
		link(temp);
		temp = nextTemp;
	}
	return out;
}
