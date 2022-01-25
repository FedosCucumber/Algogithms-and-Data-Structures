#include <iostream>
#include <fstream>
#include <string>

std::ofstream otp;
std::ifstream inp;

class Stack {
public:	

	int* stck = new int[10000];
	size_t length = 0;



	void push(int x) {
		length++;
		stck[length - 1] = x;
	}
	int pull() {
		length--;
		return stck[length];
	}
};


int main() {
	std::ios_base::sync_with_stdio(false); std::cin.tie(NULL);

	inp.open("postfix.in");
	otp.open("postfix.out");

	Stack arr;

	std::string elmnt;
	while (inp >> elmnt) {
		if (elmnt == "+") {
			int a = arr.pull();
			int b = arr.pull();
			arr.push(a + b);
		}
		else if (elmnt == "-") {
			int a = arr.pull();
			int b = arr.pull();
			arr.push(b - a);
		}
		else if (elmnt == "*") {
			int a = arr.pull();
			int b = arr.pull();
			arr.push(a * b);
		}
		else {
			arr.push(stoi(elmnt));
		}
	}
	otp << arr.stck[0];

	return 0;
}