#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>
#include <fstream>
#include <string>


class AVL_Tree {
private:
	
	typedef struct tree_node {
		int key;
		int height;
		tree_node* left;
		tree_node* right;
		tree_node(int k) {
			key = k;
			height = 1;
			left = nullptr;
			right = nullptr;
		}
		tree_node(int indx, std::vector <std::vector<int>>& vect) {
			tree_node* left_n = (vect[indx][1]) ? new tree_node(vect[indx][1] - 1, vect) : nullptr;
			tree_node* right_n = (vect[indx][2]) ? new tree_node(vect[indx][2] - 1, vect) : nullptr;

			key = vect[indx][0];
			left = left_n;
			right = right_n;

			int new_height = (left) ? left->height : 0;
			new_height = (right && right->height > new_height) ? right->height : new_height;
			height = new_height + 1;
		}
	} tree_node;

	int get_max(tree_node* root) {
		while (root->right)
			root = root->right;
		return root->key;
	}
public:
	int get_balabenc(tree_node* node) {
		if (!node) return 0;
		return get_height(node->right) - get_height(node->left);
	}
	int get_height(tree_node* node) {
		if (node)
			return node->height;
		else
			return 0;
	}
	tree_node* head;
	AVL_Tree() {
		head = nullptr;
	}
	AVL_Tree(std::vector <std::vector<int>> & vect) {
		if (vect.empty())
			head = nullptr;
		else
			head = new tree_node(0, vect);
	}
	
	tree_node* rotate_left(tree_node* node) {
		if (!node->right) return  node;
		tree_node* temp = node->right;
		node->right = temp->left;
		temp->left = node;

		node->height = std::max(get_height(node->left), get_height(node->right)) + 1;
		temp->height = std::max(get_height(temp->left), get_height(temp->right)) + 1;

		return temp;
	}

	tree_node* rotate_right(tree_node* node) {
		if (!node->left) return node;
		tree_node* temp = node->left;
		node->left = temp->right;
		temp->right = node;

		node->height = std::max(get_height(node->left), get_height(node->right)) + 1;
		temp->height = std::max(get_height(temp->left), get_height(temp->right)) + 1;

		return temp;
	}

	void rotate_big_left(tree_node* & node) {
		if (get_height(node->right->left) > get_height(node->right->right)) node->right = rotate_right(node->right);
		node = rotate_left(node);
	}

	void rotate_big_right(tree_node* & node) {
		if (get_height(node->left->left) < get_height(node->left->right)) node->left = rotate_left(node->left);
		node = rotate_right(node);
	}

	void push(tree_node* & root, int x) {
		if (head == nullptr) {
			head = new tree_node(x);
			return;
		}
		if (x < root->key) {
			if (root->left)
				push(root->left, x);
			else
				root->left = new tree_node(x);
		}
		else if (x > root->key) {
			if (root->right)
				push(root->right, x);
			else
				root->right = new tree_node(x);
		}
		else if (x == root->key)
			return;


		root->height = std::max(get_height(root->left), get_height(root->right)) + 1;
		int balabenc = get_balabenc(root);
		if (balabenc > 1)
			rotate_big_left(root);
		else if (balabenc < -1)
			rotate_big_right(root);

	}

	void delete_node(tree_node*& root, int x) {
		if (!root)
			return;
		if (x < root->key) {
			if (root->left)
				delete_node(root->left, x);
			else
				return;
		}
		else if (x > root->key) {
			if (root->right)
				delete_node(root->right, x);
			else
				return;
		}
		else {
			if (!root->left and !root->right) {
				root = nullptr;
				return;
			}
			else if (!root->left)
				root = root->right;
			else {
				tree_node* temp = root;
				int new_key = get_max(root->left);
				delete_node(root, new_key);
				temp->key = new_key;
			}
		}
		
			root->height = std::max(get_height(root->left), get_height(root->right)) + 1;
			int balabence = get_balabenc(root);
			if (balabence > 1)
				rotate_big_left(root);
			else if (balabence < -1)
				rotate_big_right(root);
	}

	void print_tree(std::vector <std::vector <int>> & output, tree_node* node, int & indx) {
		indx++;
		int cur_indx = indx;
		output[cur_indx - 1].push_back(node->key);

		if (node->left) {
			print_tree(output, node->left, indx);
			output[cur_indx - 1].push_back(cur_indx+1);
		}
		else
			output[cur_indx - 1].push_back(0);

		if (node->right) {
			output[cur_indx - 1].push_back(indx + 1);
			print_tree(output, node->right, indx);
		}
		else
			output[cur_indx - 1].push_back(0);

		return;
	}

	std::string exists(int x) {
		tree_node* node = head;
		while (node) {
			if (x < node->key)
				node = node->left;
			else if (x > node->key)
				node = node->right;
			else
				return "Y";
		}
		

		return "N";
	}
};


int main() {
	std::ifstream inp;
	inp.open("avlset.in");
	std::ofstream otp;
	otp.open("avlset.out");
	AVL_Tree tree;
	int n;
	inp >> n;
	std::string comand;
	int x;
	for (int i = 0; i < n; i++) {
		inp >> comand >> x;
		if (comand == "A") {
			tree.push(tree.head, x);
			otp << tree.get_balabenc(tree.head) << '\n';
		}
		else if (comand == "D") {
			tree.delete_node(tree.head, x);
			otp << tree.get_balabenc(tree.head) << '\n';
		}
		else if (comand == "C") {
			otp << tree.exists(x) << '\n';
		}
	}


	return 0;

}