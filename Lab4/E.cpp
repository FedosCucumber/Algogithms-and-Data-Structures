#include <iostream>
#include <fstream>

int left_binary_search(int x, int* arr, int n) {
	int left = -1;
	int right = n;
	while (left < right - 1) {
		int mid = (left + right) / 2;
		if (x > arr[mid]) {
			left = mid;
		}
		else {
			right = mid;
		}
	}
	if (arr[right] != x) {
		return -1;
	}
	else {
		return right + 1;
	}
}

int right_binary_search(int x, int* arr, int n) {
	int left = -1;
	int right = n;
	while (left < right - 1) {
		int mid = (left + right) / 2;
		if (x < arr[mid]) {
			right = mid;
		}
		else {
			left = mid;
		}
	}
	if (arr[left] != x) {
		return -1;
	}
	else {
		return left + 1;
	}
}

int main() {

	std::ifstream inp; 
	inp.open("binsearch.in");

	std::ofstream otp;
	otp.open("binsearch.out");

	int n;
	inp >> n;
	int* arr = new int[n];
	for (int i = 0; i < n; i++) {
		inp >> arr[i];
	}
	int k;
	inp >> k;
	for (int i = 0; i < k; i++) {
		int x;
		inp >> x;
		otp << left_binary_search(x, arr, n) << ' ' << right_binary_search(x, arr, n) << '\n';
	}

	return 0;
}