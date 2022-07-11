#include "pqH.h"
#include "error.h"
#include "console.h"
#include <iostream>
pqH::pqH(){
	sz = 0;
	head = new Node;
	head -> next = NULL;
}

pqH::~pqH(){
	while(head != NULL){
		Node* front = head -> next;
		delete head;
		head = front;
	}
}

int pqH::size(){
	return sz;
}

bool pqH::isEmpty(){
	return size() == 0;
}

void pqH::push(int value,  int pri){
	Node* insPos;
	insPos = findPrev(pri);
	//create new node
	Node* toAdd = new Node();
	toAdd -> val = value;
	toAdd -> pr = pri;
	toAdd -> next = NULL;
	//insert
	Node* front = insPos -> next;
	insPos -> next = toAdd;
	toAdd -> next = front;
	sz++;
	
}
pqH::Node* pqH::findPrev(int pri){
	Node* ptr = head;
	Node* cur = head -> next;

	while(cur != NULL && (cur -> val < pri)){
		cur = cur -> next;
		ptr = ptr -> next;
	}
	return ptr;
}

int pqH::pop(){
	if(size() == 0)error("queue is empty bro");
	Node* min = head -> next;
	head -> next = min -> next;
	int res = min -> val;
	sz--;
	delete min;
	return res;
}
int pqH::front(){
	if(size() == 0)error("queue is empty bro");
	return head -> next -> val;
	return -1;
}



