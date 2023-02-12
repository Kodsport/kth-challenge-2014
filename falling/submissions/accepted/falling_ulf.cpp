//Solution by Ulf Lundström
#include <iostream>
using namespace std;

int main() {
	int D;
	cin >> D;
	if (D%2 == 1) {
		cout << (D-1)/2 << " " << (D+1)/2 << endl;
	} else if (D%4 == 0) {
		cout << D/4-1 << " " << D/4+1 << endl;
	} else {
		cout << "impossible" << endl;
	}
}
