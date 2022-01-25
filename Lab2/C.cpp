#include <iostream>
#include <fstream>

long long int inv_cnt = 0;

void merge_sort(int* m, int size) {
	int sizel = size / 2;
	int* left = new int[sizel];
	int sizer = size / 2 + size % 2;
	int* right = new int[sizer];
	for (int i = 0; i < sizel; i++) {
		left[i] = m[i];
	}
	for (int i = 0; i < sizer; i++) {
		right[i] = m[i + sizer - size % 2];
	}
	if (sizel > 1) {
		merge_sort(left, sizel);
	}
	if (sizer > 1) {
		merge_sort(right, sizer);
	}
	int l = 0, r = 0;
	for (int i = 0; i < size; i++) {
		if (l >= sizel) {
			m[i] = right[r];
			r++;
		}
		else if (r >= sizer) {
			m[i] = left[l];
			l++;
			//inv_cnt++;
		}
		else if (left[l] > right[r]) {
			m[i] = right[r];
			r++;
			inv_cnt += sizel - l;
		}
		else {
			m[i] = left[l];
			l++;
		}
	}
}

int main(void) {
	int n;
	std::ifstream inp; inp.open("inversions.in");
	std::ofstream otp; otp.open("inversions.out");
	inp >> n;
	int* m = new int[n];
	for (int i = 0; i < n; i++) {
		inp >> m[i];
	}
	merge_sort(m, n);
	otp << inv_cnt;
}