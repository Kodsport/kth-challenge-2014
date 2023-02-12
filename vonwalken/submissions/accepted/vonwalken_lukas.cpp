//Solution by lukasP (Lukáš Poláček)
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    double d;
    int n;
    cin >> d >> n;

    int x, sum = 0;
    double low = 0, high = 1;
    for (int i = 1; cin >> x; i++)
    {
        sum += x;
        double nlow = d * i  - sum;
        double nhigh = d * i - sum + 1;

        low = max(low, nlow);
        high = min(high, nhigh);
    }
    cout << ((low < high) ? "possible" : "impossible") << endl;
}
