/**********************************************
 * File: pqueue-vector.h
 *
 * A priority queue class backed by an unsorted
 * vector.
 */
#ifndef BST_Included
#define BST_Included
#include <string>
using namespace std;
class BST {
public:
	
	BST();
	
	~BST();
	
	int size();

	bool isEmpty();
	
	void push(int value);
	
	int front();
	
	int pop();
	
private:
	struct Node{
		int val;
		Node* left;
		Node* right;
	};
	Node* head;
	int sz;

	void insert(Node*& nd, int val);
	void deleteSub(Node* rt);

	int deleteNode(Node*& root);

	int findMin(Node* rt);
	int height(Node* nd);
	int diff(Node* nd);

	Node* rightR(Node* nd);
	Node* leftR(Node* nd);
	Node* right_left(Node* nd);
	Node* left_right(Node* nd);

	Node* balance(Node* rt);
};

#endif
