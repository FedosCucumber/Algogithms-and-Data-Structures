#include <iostream>
#include <algorithm>
#include <fstream>


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


int tree_height(tree_node* root) {
	if (root == NULL)
		return 0;
	else
		return std::max(tree_height(root->left), tree_height(root->right)) + 1;
}

int main() {
	std::ifstream inp;
	inp.open("height.in");
	std::ofstream otp;
	otp.open("height.out");

	int n;
	inp >> n;

	if (n == 0) {
		otp << 0;
		return 0;
	}

	for (int i = 0; i < n; i++) {
		inp >> node_list[i].key >> node_list[i].left_indx >> node_list[i].right_indx;
	}

	tree_node* root = new tree_node(node_list[0].key, node_list[0].left_indx, node_list[0].right_indx);

	otp << tree_height(root);

	return 0;
}