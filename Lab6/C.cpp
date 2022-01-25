#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

typedef struct tree_node {
	int key;
	tree_node* left;
	tree_node* right;
	tree_node* parent;
	tree_node(int x, tree_node* prnt) {
		key = x;
		left = NULL;
		right = NULL;
		parent = prnt;
	}
} tree_node;

class Tree {

public:
	tree_node* head = NULL;

	void insert(tree_node* root, int key) {
		if (root == NULL)
			head = new tree_node(key, NULL);
		else {
			bool check = false;
			while (!(check)) {
				if (key < root->key)
					if (root->left == NULL) {
						root->left = new tree_node(key, root);
						check = true;
					}
					else
						root = root->left;
				else
					if (root->right == NULL) {
						root->right = new tree_node(key, root);
						check = true;
					}
					else
						root = root->right;
			}
		}
		return;
	}

	tree_node* exists(int key) {
		tree_node* root = head;
		while (root != NULL && root->key != key) {
			if (key < root->key)
				root = root->left;
			else
				root = root->right;
		}
		return root;
	}

	int prev(int key) {
		tree_node* x = exists(key);
		bool check = false;
		if (x == NULL) {
			insert(head, key);
			x = exists(key);
			check = true;
		}

		if (x->left != NULL) {
			int a(max_node(x->left));
			if (check)
				delete_node(head, key);
			return a;
		}

		tree_node* y = x->parent;
		while (y != NULL && y->left == x) {
			x = y;
			y = x->parent;
		}
		if (check)
			delete_node(head, key);

		if (y == NULL)
			return NULL;
		else
			return y->key;
	}

	int next(int key) {
		tree_node* x = exists(key);

		bool check = false;
		if (x == NULL) {
			insert(head, key);
			x = exists(key);
			check = true;
		}

		if (x->right != NULL) {
			int a = (min_node(x->right));
			if (check)
				delete_node(head, key);
			return a;
		}

		tree_node* y = x->parent;
		while (y != NULL && y->right == x) {
			x = y;
			y = x->parent;
		}
		if (check)
			delete_node(head, key);

		if (y == NULL)
			return NULL;
		else
			return y->key;
	}


	tree_node* delete_node(tree_node* root, int key) {
		if (root == NULL)
			return root;

		if (key < root->key) {
			root->left = delete_node(root->left, key);
			if (root->left != NULL)
				root->left->parent = root;
		}
		else if (key > root->key) {
			root->right = delete_node(root->right, key);
			if (root->right != NULL)
				root->right->parent = root;
		}
		else if (root->right != NULL && root->left != NULL) {
			if (root == head) {
				head->key = next(head->key);
				head->right = delete_node(head->right, head->key);
				if (head->right != NULL)
					head->right->parent = head;
				root = head;
			}
			else {
				root->key = next(root->key);
				root->right = delete_node(root->right, root->key);
				if (root->right != NULL)
					root->right->parent = root;
			}
		}
		else {
			if (root->left != NULL) {
				if (root == head) {
					head = head->left;
					head->parent = NULL;
					root = root->left;
				}
				else
					root = root->left;
			}
			else if (root->right != NULL)
				if (root == head) {
					head = head->right;
					head->parent = NULL;
					root = root->right;
				}
				else
					root = root->right;
			else
				if (root == head) {
					head = NULL;
					root = NULL;
				}
				else
					root = NULL;
		}
		return root;
	}
private:

	int min_node(tree_node* root) {
		while (root->left != NULL)
			root = root->left;
		return root->key;
	}

	int max_node(tree_node* root) {
		while (root->right != NULL)
			root = root->right;
		return root->key;
	}
};



int main() {
	std::ifstream inp;
	inp.open("bstsimple.in");

	std::ofstream otp;
	otp.open("bstsimple.out");

	std::string command;
	Tree tree;
	int x;
	while (inp >> command >> x) {
		if (command == "insert") {
			if (tree.exists(x) == NULL)
				tree.insert(tree.head, x);
		}
		else if (command == "delete") {
			tree.delete_node(tree.head, x);
		}
		else if (command == "exists") {
			tree_node* ex = tree.exists(x);
			if (ex == NULL)
				otp << "false\n";
			else
				otp << "true\n";
		}
		else if (command == "next") {
			int y = tree.next(x);
			if (y == NULL)
				otp << "none\n";
			else
				otp << y << '\n';
		}
		else if (command == "prev") {
			int y = tree.prev(x);
			if (y == NULL)
				otp << "none\n";
			else
				otp << y << '\n';
		}
	}

	return 0;
}