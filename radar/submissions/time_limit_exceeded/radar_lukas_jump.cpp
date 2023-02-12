//Solution by lukasP (Lukáš Poláček)
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)

typedef long long ll;
int norm(int x, int m)
{
    return (x % m + m) % m;
}
vector<ll> m(3), x(3), y(3), z(3);
int dist(ll x, int y, int m)
{
    int u = norm(x - y, m);
    int v = norm(y - x, m);
    return min(u, v);
}
bool ok(ll t)
{
    rep(i,0,3)
        if (dist(t, x[i], m[i]) > y[i])
            return false;
    return true;
}
int main()
{
    rep(i,0,3) cin >> m[i];
    rep(i,0,3) cin >> x[i];
    rep(i,0,3) cin >> y[i];
    rep(i,0,3) z[i] = norm(x[i] - y[i], m[i]);

    ll res = 0;
    while (!ok(res))
    {
        vector<ll> rem(3);
        rep(i,0,3)
            rem[i] = norm(z[i] - res % m[i], m[i]);
        sort(rem.begin(), rem.end());
        int u = 0;
        while (rem[u] == 0) u++;
        res += rem[u];
    }
    cout << res << endl;
}
