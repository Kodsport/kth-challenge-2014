//Solution by lukasP (Lukáš Poláček)
#include <vector>
#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)

struct union_find {
    vector<int> e;

    union_find(int n) {
        e.assign(n, -1);
    }

    void join(int a, int b) { // union sets
        a = find(a); b = find(b);
        if (a == b) return;
        if (e[a] > e[b]) swap(a, b);
        e[a] += e[b]; e[b] = a;
    }

    int find(int x) { // Find set-head with path-compression
        if (e[x] < 0) return x;
        return e[x] = find(e[x]);
    }

    int size(int x) { // Size of the set where x is
        return -e[find(x)];
    }

};
typedef long long ll;
int main()
{
    int n; scanf("%d", &n);

    ll po = 1;
    rep(i,0,n)
        po *= n - 1;

    int sum = 0;
    rep(k,0,po)
    {
        vector<int> road(n);
        union_find u(n);
        int j = k;
        rep(i,0,n)
        {
            road[i] = j % (n - 1);
            j /= n - 1;
            if (road[i] >= i) road[i]++;
            u.join(i, road[i]);
        }

        sum += u.size(0) == n;
    }

    printf("%.9lf\n", sum / double(po));
}
