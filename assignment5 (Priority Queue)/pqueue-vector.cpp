/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "error.h"

VectorPriorityQueue::VectorPriorityQueue() {
	// TODO: Fill this in!
}

VectorPriorityQueue::~VectorPriorityQueue() {
	// TODO: Fill this in!
}

int VectorPriorityQueue::size() {
	return vec.size();
}

bool VectorPriorityQueue::isEmpty() {
	return size() == 0;
}

int VectorPriorityQueue::findPos(string val){
	int ind = 0;
	while(ind <= size()-1 && vec[ind] < val){
		ind++;
	}
	return ind;
}

void VectorPriorityQueue::enqueue(string value) {
	int pos = findPos(value);

	vec.insert(pos, value);
}

string VectorPriorityQueue::peek() {
	if(size() == 0){
		error("it's empty");
	}
	return vec[0];
}

string VectorPriorityQueue::dequeueMin() {
	if(size() == 0){
		error("it's empty");
	}
	
	string res = vec[0];
	vec.remove(0);
	return res;
}

