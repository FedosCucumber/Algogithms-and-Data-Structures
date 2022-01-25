#include <iostream>
#include <fstream>

int main(void) {
	int n;
	std::ifstream inp; inp.open("antiqs.in");
	std::ofstream otp; otp.open("antiqs.out");
	inp >> n;
	int* m = new int[n];
	for (int i = 0; i < n; i++) {
		m[i] = i+1;
	}
	for (int i = 0; i < n; i++) {
		int temp = m[i / 2];
		m[i / 2] = m[i];
		m[i] = temp;
	}
	for (int i = 0; i < n; i++) {
		otp << m[i] << " ";
	}
}