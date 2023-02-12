//Solution by lukasP (Lukáš Poláček)
#include <vector>
#include <cmath>
#include <cstdio>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)

const int MAXN = 150;
double c[MAXN][MAXN];
int main()
{
    int n; scanf("%d", &n);
    vector<double> p(n + 1);

    rep(i,0,n+1)
    {
        c[i][0] = 1;
        rep(j,1,i+1)
            c[i][j] = c[i - 1][j] + c[i - 1][j - 1];

        p[i] = pow(i - 1, i);
        rep(j,2,i-1)
            p[i] -= pow(i - j - 1, i - j) * c[i - 1][j - 1] * p[j];
    }

    printf("%.12lf\n", p[n] / pow(n - 1, n));
}
