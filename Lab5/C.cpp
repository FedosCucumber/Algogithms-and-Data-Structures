#include <iostream>
#include <vector>
#include <string>

 typedef struct key_val{
 public:    
     std::string key; 
     std::string val;
     key_val(std::string k, std::string v) {
            key = k;
            val = v;
     }
     key_val() {
         key = "";
         val = "";
     }
 } key_val;

class List {
public: 
    typedef struct list_node {
        key_val elem;
        list_node* next;
        list_node* next_node;
        list_node* prev_node;
        list_node(key_val elm, list_node* nxt) {
            elem = elm;
            next = nxt;

            next_node = nullptr;
            prev_node = nullptr;
        }
    } list_node;
    list_node* head = nullptr;

    void push_front(key_val elem) {
        list_node* temp = new list_node(elem, head);
        head = temp;
        return;
    }
};

class Map {
private:
    List::list_node* last_node = nullptr;
    const int MAP_SIZE = 35437;
    
    std::vector <List> hash_map;

    

    unsigned int poly_hash(std::string key) {
        uint64_t p = 1;
        uint64_t sum = 0;
        for (auto chr : key) {
            sum = (sum + p * ((uint64_t) chr - 'a')) % MAP_SIZE;
            p = (p * 29) % MAP_SIZE;
        }

        return sum;
    }

public:
    Map() {
        std::vector <List> temp(MAP_SIZE);
        hash_map = temp;
    }
   
    void put(std::string key, std::string val) {
        key_val temp(key, val);
        int indx = poly_hash(key);

        List::list_node* node = hash_map[indx].head;
        while (node != nullptr && node->elem.key != key)
            node = node->next;

        if (!node) {
            hash_map[indx].push_front(temp);
            if (last_node)
                last_node->next_node = hash_map[indx].head;
            hash_map[indx].head->prev_node = last_node;
            last_node = hash_map[indx].head;
        }
        else
            node->elem.val = val;
        return;
    }

    void delete_node(std::string key) {
        unsigned int indx = poly_hash(key);
        List::list_node* node = hash_map[indx].head;
        List::list_node* prev = nullptr;

        while (node != nullptr && node->elem.key != key) {
            prev = node;
            node = node->next;
        }
        if (node) {
            if (node == last_node) {
                if (last_node->prev_node)
                    last_node->prev_node->next_node = nullptr;
                last_node = node->prev_node;
                free(node);
            }
            else {
                if (node->prev_node)
                    node->prev_node->next_node = node->next_node;
                node->next_node->prev_node = node->prev_node;
            }
            if (!prev)
                hash_map[indx].head = nullptr;
            else
                prev->next = node->next;
        }
    }

    std::string get(std::string key) {
        int indx = poly_hash(key);
        std::string ans = "none";

        List::list_node* node = hash_map[indx].head;
        while (node != nullptr && node->elem.key != key)
            node = node->next;

        if (node)
            ans = node->elem.val;

        return ans;
    }

    std::string prev(std::string key) {
        unsigned int indx = poly_hash(key);
        List::list_node* node = hash_map[indx].head;

        while (node != nullptr && node->elem.key != key) {
            node = node->next;
        }
        if (node && node->prev_node)
            return node->prev_node->elem.val;
        else
            return "none";
    }

    std::string next(std::string key) {
        unsigned int indx = poly_hash(key);
        List::list_node* node = hash_map[indx].head;
        while (node != nullptr && node->elem.key != key) {
            node = node->next;
        }
        if (node && node->next_node) 
            return node->next_node->elem.val;
        else
            return "none";
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string cmnd, x, y;
    Map my_map;
    
    while (std::cin >> cmnd >> x) {
        if (cmnd == "put") {
            std::cin >> y;
            my_map.put(x, y);
        }
        else if (cmnd == "delete")
            my_map.delete_node(x);
        else if (cmnd == "get")
            std::cout << my_map.get(x) << '\n';
        else if (cmnd == "prev")
            std::cout << my_map.prev(x) << '\n';
        else if (cmnd == "next")
            std::cout << my_map.next(x) << '\n';
    }

    return 0;
}