#include <iostream>
using namespace std;

#include "BST.h"
#include "console.h"
#include "random.h"
#include <vector>

void helper(vector<vector<int>>& res, vector<int>& nums, vector<bool>& vis, vector<int>& perms){
	if(perms.size() == nums.size()){
		res.push_back(perms);
	}else{
		for(int i = 0; i < nums.size(); i++){
			if(!vis[i]){
				perms.push_back(nums[i]);
				vis[i] = true;
				helper(res, nums, vis, perms);
				vis[i] = false;
				perms.pop_back();
			}
		}
	}
}

void fill(int len, vector<int>& nums){
	for(int i = 0; i < len; i++){
		nums.push_back(randomInteger(0, 171));
	}
}

bool check(BST& qu){
	int last = INT_MIN;
	
	for(int j = 0; j < qu.size(); j++){
		int tmp = qu.pop();
		if(last > tmp)return false;
	}
	return true;
}

void testOnOrder(int len){
	// yvela permutacias vagenerireb
	// vinaidan chamatebis rigitobas mnishvneloba aqvs
	// da nebismieri rigitobistvis swori unda iyos
	// mainc shevamowmot rom yvela tanmimdevrobistvis
	// sworad imushavebs
	vector<vector<int>> res;
	vector<int> nums;
	fill(len, nums);
	vector<bool> vis(len, false);
	vector<int> perms;
	helper(res, nums, vis, perms);

	int count = 0;
	
	for(int i = 0; i < res.size(); i++){
		BST qu;
		for(int j = 0; j < res[i].size(); j++){
			qu.push(res[i][j]);
		}
		if(check(qu))count++;
	}
	cout<<"passed " << count << " test out of " <<res.size()<< endl; 
	cout << endl;
}

void largeInputCases(int len){
	BST qu;
	for(int i = 0; i < len; i++){
		qu.push(randomInteger(0, INT_MAX));
	}
	if(check(qu))cout << "passed " << endl;
	else cout << "failed " << endl;
}


void TestCases(){
	cout << "r e s u l t:" << endl;
	cout << endl;
	for(int i = 1; i < 7; i++){
		testOnOrder(i);
	}
	for(int i = 0; i < 10; i++){
		largeInputCases(1000);
	}
}

int main(){
	// amowmebs BST-s 
	TestCases();

	return -1;
}