#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>

typedef struct node {
	int key;
	int left_indx;
	int right_indx;
	node() {
		key = 0;
		left_indx = 0;
		right_indx = 0;
	}
} node;

node node_list[200001];

typedef struct tree_node {
	int key;
	tree_node* left;
	tree_node* right;

	tree_node(int k, int left_indx, int right_indx) {
		key = k;
		if (left_indx <= 0)
			left = NULL;
		else
			left = new tree_node(node_list[left_indx - 1].key, node_list[left_indx - 1].left_indx, node_list[left_indx - 1].right_indx);
		if (right_indx <= 0)
			right = NULL;
		else 
			right = new tree_node(node_list[right_indx - 1].key, node_list[right_indx - 1].left_indx, node_list[right_indx - 1].right_indx);
	}
} tree_node;

void in_order_tree_walk(std::vector <int>& arr, tree_node* root) {
	if (root->left != NULL) {
		in_order_tree_walk(arr, root->left);
	}
	arr.push_back(root->key);
	if (root -> right != NULL) {
		in_order_tree_walk(arr, root->right);
	}

	return;
}

bool check_tree(tree_node* root) {
	std::vector <int> tree_sort;
	in_order_tree_walk(tree_sort, root);
	for (int i = 1; i < tree_sort.size(); i++) {
		if (tree_sort[i] <= tree_sort[i - 1])
			return false;
	}
	return true;
}

int main() {
	std::ifstream inp;
	inp.open("check.in");
	std::ofstream otp;
	otp.open("check.out");

	int n;
	inp >> n;

	for (int i = 0; i < n; i++) {
		inp >> node_list[i].key >> node_list[i].left_indx >> node_list[i].right_indx;
	}

	tree_node* root = new tree_node(node_list[0].key, node_list[0].left_indx, node_list[0].right_indx);

	if (check_tree(root))
		otp << "YES";
	else
		otp << "NO";

	return 0;
}