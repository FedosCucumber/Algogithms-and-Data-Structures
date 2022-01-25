#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void merge_sort(string** mas, int size) {
	int  sizel = size / 2;
	string** left = new string * [sizel];
	for (int i = 0; i < sizel; i++) {
		left[i] = new string[2];
		left[i] = mas[i];
	}
	int sizer = size / 2 + size % 2; 
	string** right = new string * [sizer];
	for (int i = 0; i < sizer; i++) {
		right[i] = new string[2];
		right[i] = mas[i + sizer - size%2];
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
				mas[i] = right[r];
				r++;
			}
			else if (r >= sizer) {
				mas[i] = left[l];
				l++;
			}
			else if (left[l][0] > right[r][0]) {
				mas[i] = right[r];
				r++;
			}
			else {
				mas[i] = left[l];
				l++;
			}
		}
}

int main(void) {
	
	int n;

	ifstream inp; inp.open("race.in");
	ofstream otp; otp.open("race.out");
	inp >> n;
	string** mas = new string * [n];
	for (int i = 0; i < n; i++) {
		mas[i] = new string[2];
		inp >> mas[i][0] >> mas[i][1];
	}
	merge_sort(mas, n);
	
	otp << "=== " << mas[0][0] << " ===" << "\n" << mas[0][1] << "\n";
	for (int i = 1; i < n; i++) {
		if (mas[i][0] != mas[i - 1][0]) {
			otp << "=== " << mas[i][0] << " ===" << "\n";
		}
		otp << mas[i][1] << "\n";
	}
}