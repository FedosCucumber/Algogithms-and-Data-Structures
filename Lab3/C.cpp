#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void line_sort(std::vector <std::string>& a, int size, int pos, int length) {
	std::vector <std::string> b(1000);
	int p[26] = { 0 };
	for (int i = 0; i < size; i++) {
		p[a[i][pos] - 'a']++;
	}
	for (int i = 1; i < 26; i++) {
		p[i] += p[i - 1];
	}
	for (int i = 25; i >= 1; i--) {
		p[i] = p[i - 1];
	}
	p[0] = 0;

	for (int i = 0; i < size; i++) {
		b[p[a[i][pos] - 'a']] = a[i];
		p[a[i][pos] - 'a']++;
	}
	for (int i = 0; i < size; i++) {
		a[i] = b[i];
	}
}

int main(void) {
	std::ifstream inp;
	inp.open("radixsort.in");
	std::ofstream otp;
	otp.open("radixsort.out");

	int n, m, k;

	inp >> n >> m >> k;
	std::vector <std::string> a;

	for (int i = 0; i < n; i++) {
		std::string temp;
		inp >> temp;
		a.push_back(temp);
	}

	for (int i = m - 1; i > m - k - 1; i--) {
		line_sort(a, n, i, m);
	}


	for (int i = 0; i < n; i++) {
		otp << a[i] << '\n';
	}
	return 0;
}