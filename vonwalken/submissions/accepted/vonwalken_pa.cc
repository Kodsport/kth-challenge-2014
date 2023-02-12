#include <cstdio>
double min(double x, double y) { return x < y ? x : y; }
double max(double x, double y) { return x > y ? x : y; }
int main(void) {
	double D;
	int N, sum = 0, v;
	scanf("%lf%d", &D, &N);
	double lo = 0, hi = 1;
	for (int i = 1; i <= N; ++i) {
		scanf("%d", &v);
		sum += v;
		hi = min(hi, D*i+1-sum);
		lo = max(lo, D*i-sum);
	}
	printf("%s\n", hi >= lo ? "possible" : "impossible");
	return 0;
}
