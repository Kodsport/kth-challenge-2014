#include <cstdio>

double pr[200][200];

double Prob(int n1, int n2) {
	if (!n2) return 1;
	double &res = pr[n1][n2];
	if (res == -1) {
		res = 0;
		double pp = 1;
		for (int i = 1; i <= n2; ++i) {
			double p = 1.0*(n2-i)/(n1+n2-1);
			res += pp*(1-p)*(1.0*n1/(n1+i-1))*Prob(n1+i, n2-i);
			pp *= p;
		}
	}
	return res;
}

double Prob(int n) {
	double r = 0, pp = 1;
	for (int i = 1; i <= n; ++i) {
		double p = 1.0*(n-i)/(n-1);
		r += pp*(1-p)*Prob(i, n-i);
		pp *= p;
	}
	return r;
}

int main(void) {
	int N;
	for (int i = 0; i < 200; ++i) for (int j = 0; j < 200; ++j) pr[i][j] = -1;
	scanf("%d", &N);
	printf("%.10lf\n", Prob(N));
	return 0;
}
