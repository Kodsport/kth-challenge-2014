//Solution by lukasP (Lukáš Poláček)
#include <iostream>
#include <vector>
#include <algorithm>

#include <cstdio>
#include <complex>
#include <cmath>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)

typedef pair<double, int> pdi;
double norm(double x)
{
    while (x < 0) x += M_PI;
    while (x >= M_PI) x -= M_PI;
    return x;
}
int main()
{
    int n; scanf("%d", &n);
    vector<complex<double> > p(n);
    vector<double> r(n);

    vector<pdi> events;
    int cnt = 0;
    rep(i,0,n)
    {
        double x, y;
        scanf("%lf %lf %lf", &x, &y, &r[i]);
        p[i] = complex<double> (x, y);
        rep(j,0,i)
        {
            double b = arg(p[j] - p[i]);
            double a = asin((r[j] + r[i]) / abs(p[j] - p[i]));
            events.push_back(pdi(norm(b - a), 1));
            events.push_back(pdi(norm(b + a), -1));
            cnt += events[events.size() - 2].first > events.back().first;
        }
    }


    sort(events.begin(), events.end());
    double res = 0;
    double prev = events.back().first - M_PI;
    for (pdi w : events)
    {
        if (cnt == 0)
            res = max(res, w.first - prev);
        prev = w.first;
        cnt += w.second;
    }
    printf("%.9lf\n", res);
}
