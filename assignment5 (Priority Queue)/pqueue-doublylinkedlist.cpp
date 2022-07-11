/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	head = new Node;
	tail = new Node;

	head -> prev = NULL;
	tail -> next = NULL;
	
	head -> next = tail;
	tail -> prev = head;
	sz = 0;
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
	while(head != NULL){
		Node* front = head -> next;
		delete head;
		head = front;
	}
}

int DoublyLinkedListPriorityQueue::size() {
	return sz;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {
	return size() == 0;
}

DoublyLinkedListPriorityQueue::Node* DoublyLinkedListPriorityQueue::findPrev(string value){
	Node* cur = head -> next;
	while(cur -> next != NULL && (cur -> val < value)){
		cur = cur -> next;
	}
	return cur -> prev;
}

void DoublyLinkedListPriorityQueue::enqueue(string value) {
	Node* insPos = findPrev(value);

	Node* front = insPos -> next;
	front -> prev = NULL;
	//create Node
	Node* toAdd = new Node;
	toAdd -> val = value;
	//insert
	toAdd -> next = front;
	toAdd -> prev = insPos;
	insPos -> next = toAdd;
	front -> prev = toAdd;

	sz++;
}

string DoublyLinkedListPriorityQueue::peek() {
	if(size() == 0)error("it's empty bro ");
	string res = head -> next -> val;
	return res;
}

string DoublyLinkedListPriorityQueue::dequeueMin() {
	if(size() == 0)error("it's empty bro ");

	Node* front = head -> next -> next;
	string res = head -> next -> val;
	delete head -> next;
	
	head -> next = front;
	front -> prev = head;
	sz--;
	return res;
}

