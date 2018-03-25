#include "Node.h"

class FibonacciHeap
{
public:
	Node* minRoot;
	Node** rootListByRank;
	bool link(Node* root);
	FibonacciHeap();
	FibonacciHeap(Node*);
	~FibonacciHeap();
	bool isEmpty();
	bool insertVertex(Node*);
	void decreaseKey(int newKey, Node*);
	Node* findMin();
	Node* deleteMin();
};