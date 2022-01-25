#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

class priority_queue {
public:

	std::vector <int*> a;
	std::vector <int> indx;

	void push(int x, int step) {
		int* elmnt = new int[2];
		elmnt[0] = x;
		elmnt[1] = step;
		a.push_back(elmnt);
		indx.resize(step);
		siftUp(a.size() - 1);
	}
	int extractMin() {
		int m = a[0][0];
		swap(0, a.size() - 1);
		a.pop_back();
		a.shrink_to_fit();
		siftDown(0);
		return m;
	}
	void decreaseKey(int step, int y) {
		a[indx[step]][0] = y;
		siftUp(indx[step]);
	}

private:
	void siftUp(int pos) {
		indx.push_back(pos);

		while (a[pos][0] < a[(pos - 1) / 2][0]) {
			swap(pos, (pos - 1) / 2);
			pos = (pos - 1) / 2;
			if (pos == 0) break;
		}
	}

	void siftDown(int pos) {
		while (pos * 2 + 1 < a.size()) {
			int left = pos * 2 + 1;
			int right = pos * 2 + 2;
			int min = pos;
			if (left < a.size()) if (a[min][0] > a[left][0]) {
				min = left;
			}
			if (right < a.size()) if (a[min][0] > a[right][0]) {
				min = right;
			}
			if (min != pos) {
				swap(min, pos);
				pos = min;
			}
			else break;
		}

	}

	void swap(int i, int j) {
		int* temp = a[i];
		a[i] = a[j];
		a[j] = temp;
		int t = indx[a[i][1]];
		indx[a[i][1]] = indx[a[j][1]];
		indx[a[j][1]] = t;
	}
};

int main() {
	std::ifstream inp;
	inp.open("priorityqueue.in");
	std::ofstream otp;
	otp.open("priorityqueue.out");

	priority_queue q;
	std::string line;
	int step = 0;

	while (inp >> line) {
		if (line == "push") {
			int x;
			inp >> x;
			q.push(x, step);
		}
		else if (line == "extract-min") {
			if (q.a.size() == 0) {
				otp << "*\n";
			}
			else otp << q.extractMin() << '\n';
		}
		else {
			int x, y;
			inp >> x >> y;
			q.decreaseKey(x - 1, y);
		}
		step++;
	}
	return 0;
}