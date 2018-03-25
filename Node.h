#include <iostream>
#include <cmath>
#include <cstdlib>


enum State
{
	LABELED, UNLABELED, SCANNED
};

using namespace std;


// node declaration
struct Node
{
	Node* parent;
	Node* children;
	Node* leftSibling;
	Node* rightSibling;
	int index;
	int key;
	int rank;
	int state;
	bool addChild(Node*);
	bool addSibling(Node*);
	bool remove();
	Node* leftMostSibling();
	Node* rightMostSibling();
	Node(int _index, int _key);
	Node();
};

