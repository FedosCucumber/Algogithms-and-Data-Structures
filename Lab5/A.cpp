#include <iostream>
#include <vector>
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

class Set {
private:
    const int set_size = 100003;
    std::vector <Tree> heads;

    int hash(int x) {
        return abs(x) % set_size;
    }
public:
    Set() {
        std::vector <Tree> temp(set_size);
        heads = temp;
    }

    bool exists(int x) {
        return heads[hash(x)].exists(x);
    }

    void insert(int x) {
        if (!heads[hash(x)].exists(x))
            heads[hash(x)].insert(heads[hash(x)].head, x);

        return;
    }

    void delete_key(int x) {
        heads[hash(x)].delete_node(heads[hash(x)].head, x);

        return;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false); 
    std::cin.tie(NULL);
    int x;
    std::string command;
    Set my_set;
    while (std::cin >> command >> x) {
        if (command == "insert")
            my_set.insert(x);
        else if (command == "exists") {
            if (my_set.exists(x))
                std::cout << "true\n";
            else
                std::cout << "false\n";
        }
        else
            my_set.delete_key(x);
    }


    return 0;
}