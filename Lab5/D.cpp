#include <iostream>
#include <vector>
#include <list>
#include <utility>


class Values {
private:
	
	const size_t VALUES_TABLE_SIZE = 101;
	size_t values_hash(std::string val) {
		size_t hash_val = 0;
		const unsigned int m = 822823;
		unsigned long int p = 1;
		for (char a : val) {
			hash_val = (hash_val + a * p) % 101;
			p = (p * 2) % 101;
		}

		return hash_val % VALUES_TABLE_SIZE;
	}
public:
	std::vector <std::list<std::string>> values_table;
	int num_values;
	Values() {
		std::vector <std::list<std::string>> temp(VALUES_TABLE_SIZE);
		values_table = temp;
		num_values = 0;
	}

	void add(std::string val) {
		size_t indx = values_hash(val);

		for (std::list <std::string>:: iterator it = values_table[indx].begin(); it != values_table[indx].end(); it++)
			if (*it == val) {
				return;
			}
		num_values++;
		values_table[indx].push_front(val);
		return;
	}

	void delete_val(std::string val) {
		size_t indx = values_hash(val);
		if (values_table[indx].empty())
			return;

		for (std::list<std::string> ::iterator it = values_table[indx].begin(); it != values_table[indx].end(); it++)
			if (*it == val) {
				values_table[indx].erase(it);
				num_values--;
				return;
			}
		
		return;
	}

	std::string get_values() {
		std::string values = "";
		for (std::list <std::string> & lst : values_table) {
			if (lst.empty())
				continue;
			else
				for (std::list <std::string>::iterator it =lst.begin(); it != lst.end(); it++)
					values += " " + *it;
		}

		return values;
	}
};

class Multi_map {
private: 
	typedef std::pair <std::string, Values> key_values;
	const size_t MAP_SIZE = 101;
	
	size_t keys_hash(std::string key) {
		size_t hash_sum = 0;
		const unsigned int m = 822823;
		unsigned long int p = 1;
		for (char a : key) {
			hash_sum = (hash_sum + a * p) % 101;
			p = (p * 2) % 101;
		}

		return hash_sum % MAP_SIZE;
	}
public:
	std::vector <std::list <key_values>> keys_table;
	Multi_map() {
		keys_table.resize(MAP_SIZE);
	}

	void add(std::string key, std::string val) {
		size_t indx = keys_hash(key);
		for (auto & map_elem : keys_table[indx])
			if (map_elem.first == key) {
				map_elem.second.add(val);
				return;
			}
		key_values k;
		keys_table[indx].push_front(k);
		keys_table[indx].front().first = key;
		keys_table[indx].front().second.add(val);
		return;
	}

	void delete_val(std::string key, std::string val) {
		size_t indx = keys_hash(key);
		for (auto & map_elem : keys_table[indx])
			if (map_elem.first == key) {
				map_elem.second.delete_val(val);
				return;
			}

		return;
	}

	void delete_key(std::string key) {
		size_t indx = keys_hash(key);
		for (std::list <key_values> ::iterator it = keys_table[indx].begin(); it != keys_table[indx].end(); it++)
			if (it->first == key) {
				keys_table[indx].erase(it);
				return;
			}

		return;
	}

	void get(std::string key) {
		size_t indx = keys_hash(key);
		for (auto & map_elem : keys_table[indx])
			if (map_elem.first == key) {
				std::cout << map_elem.second.num_values << map_elem.second.get_values() << '\n';
				return;
			}

		std::cout << "0\n";

		return;
	}
};


int main() {
	std::string cmd, x, y;
	Multi_map my_map;
	while (std::cin >> cmd >> x) {
		if (cmd == "put") {
			std::cin >> y;
			my_map.add(x, y);
		}
		else if (cmd == "delete") {
			std::cin >> y;
			my_map.delete_val(x, y);
		}
		else if (cmd == "deleteall")
			my_map.delete_key(x);
		else if (cmd == "get")
			my_map.get(x);
		else {
			std::cout << "HEY, DJ, TI CHTO, EBAN?\n";
			return 1;
		}
	}

	return 0;
}