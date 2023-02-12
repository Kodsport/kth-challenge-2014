//Solution by lukasP (Lukáš Poláček)
#include <vector>
#include <cmath>
#include <cstdio>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)

const int MAXN = 2010;
double c[MAXN][MAXN];
int main()
{
    int n; scanf("%d", &n);
    vector<double> p(n + 1);

    rep(i,0,n+1)
    {
        c[i][0] = 1;
        if (i + 1 < MAXN) c[i][i + 1] = 0;
        rep(j,1,i+1)
            c[i][j] = c[i - 1][j] + c[i - 1][j - 1];

        p[i] = 1;
        rep(j,2,i-1)
            p[i] -= pow((i - j - 1) / (i - 1.), i) * pow((j - 1) / (i - j - 1.), j) *
                    p[j] * c[i - 1][j - 1];
    }

    printf("%.9lf\n", p[n]);
}
