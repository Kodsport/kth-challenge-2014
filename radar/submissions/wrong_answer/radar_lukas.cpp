//Solution by lukasP (Lukáš Poláček)
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)

typedef long long ll;
struct F
{
    ll x, y, d;
    F(ll xx, ll yy, ll dd) : x(xx), y(yy), d(dd) {}
};
F gcd(ll a, ll b)
{
    if (a == 0) return F(0, 1, b);
    F f = gcd(b % a, a);
    return F(f.y - b / a * f.x, f.x, f.d);
}
ll inver(ll a, ll m)
{
    return (m + gcd(a, m).x) % m;
}

ll M;
vector<ll> iM(3), dM(3);
ll cinska_zvyskova(vector<ll> m, vector<ll> x)
{
    ll res = 0;
    for (unsigned i = 0; i < m.size(); i++)
        res += dM[i] * (iM[i] * x[i] % m[i]);
    return res % M;
}
int norm(int x, int m)
{
    return (x % m + m) % m;
}
int main()
{
    vector<ll> m(3), x(3), y(3);
    rep(i,0,3) cin >> m[i];
    M = accumulate(m.begin(), m.end(), 1LL, multiplies<ll>());
    rep(i,0,3)
    {
        dM[i] = M / m[i];
        iM[i] = inver(dM[i], m[i]);
    }

    rep(i,0,3) cin >> x[i];
    rep(i,0,3) cin >> y[i];

    ll res = 1LL<<62;

    bool ok0 = true;
    rep(l,0,3) if (!(y[l] >= x[l] || x[l] + y[l] >= m[l]))
        ok0 = false;

    if (ok0)
    {
        cout << 0 << endl;
        return 0;
    }

    rep(l,0,3)
    {
        int r[3][2];
        rep(i,0,3)
        {
            r[i][0] = norm(x[i] - y[i], m[i]);
            if (i != l) r[i][1] = x[i] + y[i];
            else r[i][1] = r[i][0];
        }

        for (int i = r[0][0]; i <= r[0][1]; i++)
            for (int j = r[1][0]; j <= r[1][1]; j++)
                for (int k = r[2][0]; k <= r[2][1]; k++)
                {
                    vector<ll> rem = {i, j, k};
                    res = min(res, cinska_zvyskova(m, rem));
                }
    }
    cout << res << endl;
}
