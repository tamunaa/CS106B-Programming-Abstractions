#ifndef pqH_Included
#define pqH_Included

#include <vector>
#include <stack>
using namespace std;

class pqH{
public:
	pqH();
	~pqH();
	int size();
	bool isEmpty();
	void push(int val, int pri);
	int pop();
	int front();
private:
	// yovel ricxvs mivaniwot tavis prioriteti
	// users sheedzlos am ricxvis prioritetis archeva
	struct Node{
		int val;
		int pr;
		Node* next;
	};
	Node* head;
	Node* findPrev(int value);
	int sz;
	
};

#endif