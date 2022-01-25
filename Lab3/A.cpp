#include <iostream>
#include <fstream>

int a[100001];
int main(void)
{
	std::ifstream inp;
	inp.open("isheap.in");
	std::ofstream otp;
	otp.open("isheap.out");
	int n;
	inp >> n;
	bool check = true;
	for (int i = 1; i <= n; i++) {
		inp >> a[i];
	}
	for (int i = 1; i * 2 <= n; i++) {
		if (a[i] > a[i * 2]) check = false;
		if (i * 2 + 1 <= n) if (a[i] > a[i * 2 + 1]) check = false;
	}
	if (check) {
		otp << "YES";
	}
	else {
		otp << "NO";
	}
	return 0;
}