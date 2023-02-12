//Solution by Ulf Lundström
#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

typedef pair<double,bool> pdb;

int main() {
	int N;
	cin >> N;
	vector<double> x(N), y(N), r(N);
	for (int i = 0; i < N; ++i) {
		cin >> x[i] >> y[i] >> r[i];
	}
	vector<pdb> events;
	for (int i = 0; i < N; ++i) {
		for (int j = i+1; j < N; ++j) {
			double dx = x[i]-x[j], dy = y[i]-y[j];
			double a = atan2(dy,dx);
			if (a < 0) a += M_PI;
			double b = asin((r[i]+r[j])/sqrt(dx*dx + dy*dy));
			double start = a-b, end = a+b;
			events.push_back(pdb(start,true));
			events.push_back(pdb(end,false));
			if (start < 0) {
				events.push_back(pdb(start+M_PI,true));
				events.push_back(pdb(end+M_PI,false));
			}
			if (end > M_PI) {
				events.push_back(pdb(start-M_PI,true));
				events.push_back(pdb(end-M_PI,false));
			}
		}
	}
	double best = 0;
	int depth = 0;
	sort(events.begin(),events.end());
	events.push_back(pdb(events[0].first+M_PI,true));
	for (int i = 0; i < events.size()-1; ++i) {
		if (events[i].second)
			depth++;
		else {
			depth--;
			if (depth == 0)
				best = max(best,events[i+1].first-events[i].first);
		}
	}
	printf("%.9lf\n",best);
}
