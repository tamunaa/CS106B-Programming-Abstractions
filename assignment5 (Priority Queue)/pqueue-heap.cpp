/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
 
#include "pqueue-heap.h"
#include "error.h"

int const startSize = 32;

HeapPriorityQueue::HeapPriorityQueue() {
	data = new string[startSize];
	sz = 0;
	fakeSize = startSize;
}

HeapPriorityQueue::~HeapPriorityQueue() {
	delete[] data;
}

int HeapPriorityQueue::size() {
	return sz;
}

bool HeapPriorityQueue::isEmpty() {
	return sz == 0;
}

void HeapPriorityQueue::grow(){
	string* tmp = new string[2 * sz];
	for(int i = 0; i < sz; i++){
		tmp[i] = data[i];
	}
	delete[] data;
	data = tmp;
	fakeSize *= 2;
}

void HeapPriorityQueue::enqueue(string value) {
	if(fakeSize == size())grow();
	int ind = sz;
	data[ind] = value;
	while(ind >= 1 && data[(ind-1)/2] > value){
		string tmp = data[(ind-1)/2];
		data[(ind-1)/2] = value;
		data[ind] = tmp;

		ind = (ind - 1)/2;
	}
	sz++;
}

string HeapPriorityQueue::peek() {
	if(size() == 0)error("emptyyy");
	return data[0];
}

string HeapPriorityQueue::dequeueMin() {
	if(size() == 0)error("emptyyy");
	string res = data[0];
	int ind = 0;
	//tavshi chavsvam bolo elements
	//da mere gadavsvapav swor indexze
	data[ind] = data[sz-1];
	sz--;
	//sanam orive svili yavs
	while(2*ind + 2 < sz){
		string str = min(data[2*ind+1], data[2*ind + 2]);

		if(data[ind] > str){
			if(data[2*ind+1] < data[2*ind+2]){
				data[2*ind+1] = data[ind];
				data[ind] = str;
				//gadavidet axal shvilze
				ind = ind *2 + 1;
			}else{
				data[2*ind + 2] = data[ind];
				data[ind] = str;
				ind = ind * 2 + 2;
			}
		}else break;
	}
	//tu kide yavs marcxena shvili
	if(ind * 2 + 1 < sz){
		if(data[2*ind + 1] < data[ind]){
			string tmp = data[ind];
			data[ind] = data[2*ind + 1];
			data[2*ind + 1] = tmp;
		}
	}
	return res;
}

