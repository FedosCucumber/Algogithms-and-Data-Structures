#include <iostream>
#include <fstream>
#include <vector>

void heapify(std::vector <int>& A, int pos, int heap_size) {
	int left = pos * 2 + 1;
	int right = pos * 2 + 2;
	int max_pos = pos;

	if (left < heap_size) {
		if (A[left] > A[max_pos]) {
			max_pos = left;
		}
	}

	if (right < heap_size) {
		if (A[right] > A[max_pos]) {
			max_pos = right;
		}
	}

	if (A[max_pos] > A[pos]) {
		int temp;
		temp = A[pos];
		A[pos] = A[max_pos];
		A[max_pos] = temp;
		heapify(A, max_pos, heap_size);
	}
}

int main(void)
{
	std::ifstream inp;
	inp.open("sort.in");
	std::ofstream otp;
	otp.open("sort.out");

	std::vector <int> A;
	int n;
	inp >> n;
	for (int i = 0; i < n; i++) {
		int temp;
		inp >> temp;
		A.push_back(temp);
	}
	int heap_size = A.size();
	for (int i = n / 2; i >= 0; i--) {
		heapify(A, i, heap_size);
	}
	for (int i = n - 1; i >= 0; i--) {
		int temp = A[0];
		A[0] = A[i];
		A[i] = temp;
		heapify(A, 0, --heap_size);
	}
	for (int i = 0; i < n; i++) {
		otp << A[i] << " ";
	}
}