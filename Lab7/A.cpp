#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>
#include <fstream>



typedef struct {
	int balance;
	int left;
	int right;
} node;

std::vector <node> tree;

int get_balance(int indx) {
	int left_height = (tree[indx].left) ? get_balance(tree[indx].left - 1) : 0;
	int right_height = (tree[indx].right) ? get_balance(tree[indx].right - 1) : 0;

	tree[indx].balance = right_height - left_height;

	return std::max(left_height, right_height) + 1;
}





int main() {
	std::ifstream inp;
	inp.open("balance.in");
	std::ofstream otp;
	otp.open("balance.out");

	int n;
	inp >> n;
	for (int i = 0; i < n; i++) {
		node temp;
		int t;
		inp >> t >> temp.left >> temp.right;
		tree.push_back(temp);
	}

	get_balance(0);

	for (int i = 0; i < n; i++)
		otp << tree[i].balance << '\n';

	
	return 0;
}