#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int m, b, M, B, tm, tb;
    cin >> m >> b >> M >> B >> tm >> tb;
    for (int i = 0; i < 2; ++i) {
        int t1 = (m) + (m-M);
        int t2 = t1 + (M-b) + (b-B);
        if (t1 <= tm && t2 <= tb) {
            cout << "possible" << endl;
            return 0;
        }
        swap(m, b);
        swap(M, B);
        swap(tm, tb);
    }
    cout << "impossible" << endl;
}
