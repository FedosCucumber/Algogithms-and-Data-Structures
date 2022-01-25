#include <iostream>
#include <fstream>

void qusort(int* a, int left, int right, int k) {
	int l = left, r = right;
	int mid = a[(r + l) / 2];
	while (l <= r) {
		while (a[l] < mid) {
			l++;
		}
		while (a[r] > mid) {
			r--;
		}
		if (l <= r) {
			int temp = a[l];
			a[l] = a[r];
			a[r] = temp;
			l++;
			r--;
		}
	}
	if (k <= r) qusort(a, left, r, k);
	if (k >= l) qusort(a, l, right, k);
}

int main(void) {
	std::ifstream inp; inp.open("kth.in");
	std::ofstream otp; otp.open("kth.out");
	int n, k;
	//std::cin >> n >> k;
	inp >> n >> k;
	int* a = new int[30000000];
	int A, B, C;
	//std::cin >> A >> B >> C >> a[0] >> a[1];
	inp >> A >> B >> C >> a[0] >> a[1];
	for (int i = 2; i < n; i++) {
		a[i] = A * a[i - 2] + B * a[i - 1] + C;
	}
	k--;
	qusort(a, 0, n - 1, k);
	/*for (int i = 0; i < n; i++) {
		std::cout << a[i] << " ";
	}*/
	//std::cout << a[k];
	otp << a[k];
}