#include <iostream>
#include <cstdlib>
#include <vector> 

using namespace std;

void qusort( vector <int> &mas) {
	vector <int> low;
	vector <int> mid;
	vector <int> high;
	int piv = mas[rand() % mas.size()];
	for (int i = 0; i < mas.size(); i++) {
		if (mas[i] < piv) {
			low.push_back(mas[i]);
		}
		else if (mas[i] > piv) {
			high.push_back(mas[i]);
		}
		else {
			mid.push_back(mas[i]);
		}
	}
	if (low.size() > 1) {
		qusort(low);
	}
	if (high.size() > 1) {
		qusort(high);
	}
	low.insert(low.end(), mid.begin(), mid.end());
	low.insert(low.end(), high.begin(), high.end());
	mas = low;
}

int main(void) {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n;
	cin >> n;
	vector <int> mas;
	for (int i = 0; i < n; i++) {
		int temp;
		cin >> temp;
		mas.push_back(temp);
	}
	qusort(mas);
	for (int i = 0; i < n; i++) {
		cout << mas[i] << " ";
	}
	return 0;
}