/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include "error.h"

LinkedListPriorityQueue::LinkedListPriorityQueue() {
	sz = 0;
	head = new Node;
	head -> next = NULL;
}

LinkedListPriorityQueue::~LinkedListPriorityQueue() {
	while(head != NULL){
		Node* front = head -> next;
		delete head;
		head = front;
	}
}

int LinkedListPriorityQueue::size() {
	return sz;
}

bool LinkedListPriorityQueue::isEmpty() {
	return sz == 0;
}

LinkedListPriorityQueue::Node* LinkedListPriorityQueue::findPrev(string value){
	Node* ptr = head;
	Node* cur = head -> next;

	while(cur != NULL && (cur -> val < value)){
		cur = cur -> next;
		ptr = ptr -> next;
	}
	return ptr;
}

void LinkedListPriorityQueue::enqueue(string value) {
	Node* insPos;
	insPos = findPrev(value);
	//create new node
	Node* toAdd = new Node();
	toAdd -> val = value;
	toAdd -> next = NULL;
	//insert
	Node* front = insPos -> next;
	insPos -> next = toAdd;
	toAdd -> next = front;
	sz++;
}

string LinkedListPriorityQueue::peek() {
	if(size() == 0)error("queue is empty bro");
	return head -> next -> val;
}

string LinkedListPriorityQueue::dequeueMin() {
	if(size() == 0)error("queue is empty bro");
	Node* min = head -> next;
	head -> next = min -> next;
	string res = min -> val;
	sz--;
	delete min;
	return res;
}

