#include <iostream>
#include <fstream>

std::ofstream otp;
std::ifstream inp;

class Stack {
	
	int* stck = NULL;
	size_t length = 0;

public:

	void push(int x) {
		int* new_stck = new int[++length];
		memcpy(new_stck, stck, (length - 1) * sizeof(int));
		new_stck[length - 1] = x;
		delete[] stck;
		stck = new_stck;
		return;
	}
	void pull() {
		//std::cout << stck[0] <<'\n';
		otp << stck[0] << '\n';
		stck++;
		int* new_stck = new int[--length];
		memcpy(new_stck, stck, length * sizeof(int));
		delete[] --stck;
		stck = new_stck;
		return;
	}
};


int main() {

	inp.open("queue.in");
	otp.open("queue.out");

	int n;

	Stack arr;

	//std::cin >> n;
	inp >> n;
	for (int i = 0; i < n; i++) {
		char cmnd;
		//std::cin >> cmnd;
		inp >> cmnd;
		if (cmnd == '+') {
			int x;
			//std::cin >> x;
			inp >> x;
			arr.push(x);
		}
		else {
			arr.pull();
		}
	}
}