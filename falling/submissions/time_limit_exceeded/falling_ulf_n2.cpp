//Solution by Ulf Lundström
#include <iostream>
using namespace std;

int main() {
	int D;
	cin >> D;
	for (int n1 = 0; n1 <= D/2; ++n1) {
		for (int n2 = n1; n2 <= (D+1)/2; ++n2) {
			if (n2*n2 - n1*n1 == D) {
				cout << n1 << " " << n2 << endl;
				return 0;
			}
		}
	}
	cout << "impossible" << endl;
}
