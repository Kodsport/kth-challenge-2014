#include <algorithm>
#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;

typedef pair<double, double> pdd;
typedef vector<pdd> vpd;
const double pi = 2.0*acos(0.0);

double sqr(double x) { return x*x; }

int main(void) {
	double x[200], y[200], r[200];
	int N;
	vpd ival;
	scanf("%d", &N);
	for (int i = 0; i < N; ++i)
		scanf("%lf%lf%lf", x+i, y+i, r+i);
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j) {
			if (i == j) continue;
			double d = sqrt(sqr(x[i]-x[j])+sqr(y[i]-y[j]));
			double v = atan2(y[j]-y[i], x[j]-x[i]);
			double th = pi/2-acos((r[i]+r[j])/d);
			ival.push_back(pdd(v-2*pi-th, v-2*pi+th));
			ival.push_back(pdd(v-th, v+th));
			ival.push_back(pdd(v+2*pi-th, v+2*pi+th));
		}
	sort(ival.begin(), ival.end());
	double res = 0, at = ival.front().first;
	for (int i = 0; i < ival.size(); ) {
		int j = i;
		if (at > -pi && at < pi) res = max(res, ival[i].first-at);
		double end = ival[i].second;
		while (j+1 < ival.size() && ival[j+1].first <= end)
			end = max(end, ival[j+1].second), ++j;
		at = end;
		i = j+1;
	}
	printf("%.10lf\n", res);
}
