#include <iostream>
#include <fstream>

int main() {
	std::ifstream inp;
	inp.open("garland.in");
	std::ofstream otp;
	otp.open("garland.out");

	double A;
	int n;

	inp >> n >> A;

	double low = 0;
	double high = A;

	double* garland = new double[n];
	garland[0] = A;
	double B;
	while (high - low > 0.00001) {
		garland[1] = (low + high) / 2;
		int flg = 1;
		for (int i = 2; i < n; i++) {
			garland[i] = garland[i - 1] * 2 - garland[i - 2] + 2;
			if (garland[i] < 0) {
				flg = 0;
				break;
			}
		}
		if (flg) {
			high = garland[1];
			B = garland[n - 1];
		}
		else {
			low = garland[1];
		}
	}

	otp << std::fixed << B;
	return 0;
}