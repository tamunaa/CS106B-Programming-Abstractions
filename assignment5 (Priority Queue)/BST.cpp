#include "BST.h"
#include "error.h"

BST::BST(){
	sz = 0;
	head = NULL;
}

BST::~BST(){
	 deleteSub(head);
}

int BST::size(){
	return sz;
}

int BST::height(Node* nd){
	if(nd == NULL)return 0;
	return 1 + max(height(nd -> left), height(nd -> right));
}

BST::Node* BST::rightR(Node* nd){
	Node* tmp; tmp = nd -> left;
	
	nd -> left = tmp -> right;
	tmp -> right = nd;

	return tmp;
}

BST::Node* BST::leftR(Node* nd){
	Node* tmp; tmp = nd -> right;
	
	nd -> right = tmp -> left;
	tmp -> left = nd;

	return tmp;
}

BST::Node* BST::right_left(Node* nd){
	nd -> right = rightR(nd -> right);

	return leftR(nd);
}

BST::Node* BST::left_right(Node* nd){
	nd -> left = leftR(nd -> left); 

	return rightR(nd);
}

int BST::diff(Node* nd){
	int l = height(nd -> left);
	int r = height(nd -> right);

	return l - r;
}

void BST::deleteSub(Node* rt) {
	if (rt == NULL) {
		return;
	}
	deleteSub(rt->left);
	deleteSub(rt->right);
	delete rt;
}

bool BST::isEmpty(){
	return size() == 0;
}
int BST::findMin(Node* rt){
	if(rt == NULL)return INT_MAX;
	int res = rt -> val;
	return min(res, min(findMin(rt -> left), findMin(rt -> right)));
}

int BST::deleteNode(Node*& rt) {
	if(rt -> left == NULL){
		int res = rt -> val;
		Node* p = rt;
		rt = rt -> right;
		delete p;
		return res;
	}else{
		return deleteNode(rt->left);
	}
}

BST::Node* BST::balance(Node* rt){
	int delta = diff(rt);
	// marcxniv ufro meti noudi maqvs
	// da unda movabruno marjvniv

	if(delta > 1){
		if(diff(rt -> left) > 0){
			rt = rightR(rt);
		}else{
			rt = left_right(rt);
		}
	}else if(delta < -1){ // marjvniv ufro meti shvili yavs
		if(diff(rt -> right) > 0){
			rt = right_left(rt);
		}else{
			rt = leftR(rt);			
		}
	}
	return rt;
}

void BST::insert(Node*& rt, int val){
	if(rt == NULL){
		Node* nd = new Node;
		nd -> val = val;
		nd -> left = NULL; nd -> right = NULL;
		rt = nd;
		return;
	}
	if(rt -> val > val){
		insert(rt -> left, val);
	}else{
		insert(rt -> right, val);
	}
	//davabalansot radgan cud ceisebshi
	//dzebnas o(n) daswirdeba
	rt = balance(rt);
}


void BST::push(int value){
	insert(head, value);
	sz++;
}

int BST::pop(){
	if(size() == 0)error("emptyyyy");
	sz--;
	return deleteNode(head);
}

int BST::front(){
	if(size() == 0)error("emptyyyy");
	int res = findMin(head);
	return res;
}



