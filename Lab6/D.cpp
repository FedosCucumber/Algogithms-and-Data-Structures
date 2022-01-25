#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <fstream>
#include <cinttypes>

	std::queue <uint16_t> qu;
	std::map <std::string, int> labels;
	int com_count;
	std::map <char, void (*)(std::string)> commands;
	
	uint16_t arr[26];

	void add(std:: string cmd) { // +
		uint16_t x = qu.front();
		qu.pop();
		uint16_t y = qu.front();
		qu.pop();
		qu.push((x + y) % 65536);

		return;
	}

	void sub(std::string cmd) { // -
		uint16_t x = qu.front();
		qu.pop();
		uint16_t y = qu.front();
		qu.pop();

		qu.push((x - y) % 65536);

		return;
	}

	void mlt(std::string cmd) { // *
		uint16_t x = qu.front();
		qu.pop();
		uint16_t y = qu.front();
		qu.pop();

		qu.push((x * y) % 65536);

		return;
	}
	
	void div(std::string cmd) { // /
		uint16_t x = qu.front();
		qu.pop();
		uint16_t y = qu.front();
		qu.pop();
		if (y == 0)
			qu.push(0);
		else
			qu.push((x / y) % 65536);

		return;
	}

	void mod(std::string cmd) { // %
		uint16_t x = qu.front();
		qu.pop();
		uint16_t y = qu.front();
		qu.pop();
		if (y == 0)
			qu.push(0);
		else
			qu.push((x % y) % 65536);

		return;
	}
	void place_reg(std:: string indx)  { // >[register]
		arr[indx[1] - 'a'] = qu.front();
		qu.pop();

		return;
	}

	void get_reg(std::string indx) { // <[register]
		qu.push(arr[indx[1] - 'a']);

		return;
	}

	void print(std::string indx) { // P 
		if (indx.length() == 1) {
			std::cout << qu.front() << '\n';
			qu.pop();
		}
		else {
			std::cout << arr[indx[1] - 'a'] << '\n';
		}

		return;
	}

	void print_char(std::string indx) { // C
		if (indx.length() == 1) {
			std::cout << (char) (qu.front() % 256);
			qu.pop();
		}
		else {
			std::cout << (char) (arr[indx[1] - 'a'] % 256);
		}

		return;
	}

	void tag(std::string label) { // :
		labels[label.substr(1)] = com_count;

		return;
	}

	void go_to(std::string label) { // J
		com_count = labels[label.substr(1)];

		return;
	}
	void beq(std::string reg_label) { // Z
		if (!arr[reg_label[1] - 'a']) {
			com_count = labels[reg_label.substr(2)];
		}

		return;
	}


	void bmi(std::string cmnd) { // E
		if (arr[cmnd[1] - 'a'] == arr[cmnd[2] - 'a'])
			com_count = labels[cmnd.substr(3)];

		return;
	}
	
	void bml(std::string cmnd) { // G
		if (arr[cmnd[1] - 'a'] > arr[cmnd[2] - 'a'])
			com_count = labels[cmnd.substr(3)];

		return;
	}

	void init_coms() {
		commands['+'] = add;
		commands['-'] = sub;
		commands['*'] = mlt;
		commands['/'] = div;
		commands['%'] = mod;
		commands['>'] = place_reg;
		commands['<'] = get_reg;
		commands['P'] = print;
		commands['C'] = print_char;
		commands[':'] = tag;
		commands['J'] = go_to;
		commands['Z'] = beq;
		commands['E'] = bmi;
		commands['G'] = bml;
	}

int main() {

	std::string cmnd;
	std::vector <std::string> prog;
	init_coms();
	com_count = 0;
	while (std::cin >> cmnd) {
		prog.push_back(cmnd);
		if (cmnd[0] == ':') {
			tag(cmnd);
		}
		com_count++;
	}

	for (com_count = 0; com_count < prog.size(); com_count++) {
		if (prog[com_count][0] >= '0' && prog[com_count][0] <= '9')
			qu.push((uint16_t) std::stoi(prog[com_count]) % 65536);
		else if (prog[com_count] == "Q")
			return 0;
		else if (prog[com_count][0] != ':') {
			void (*func)(std::string) = commands[prog[com_count][0]];
			(*func)(prog[com_count]);
		}
	}

	return 0;
}
