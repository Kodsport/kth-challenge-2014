//Solution by Erik Aas
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;

inline int dist(int a, int b, int m) {
	if(a<=b) return min(b-a, a-b+m);
					return min(a-b, b-a+m);
}

ll r[512], q[512], s[512], t[512];
void gcd(ll a, ll b, ll&x, ll&y) {
	//find x,y such that ax+by=gcd(a,b)
	//requires a > b
	s[0] = 1; s[1] = 0;
	t[0] = 0; t[1] = 1;
	r[0] = a; r[1] = b;
	int k;
	for(k=1;;++k) {
		q[k  ] = r[k-1] / r[k];
		r[k+1] = r[k-1] % r[k];
		s[k+1] = s[k-1]-q[k]*s[k];
		t[k+1] = t[k-1]-q[k]*t[k];
		if(r[k+1] == 0) break;
	}
	//gcd = r[k];
	x = s[k]; y = t[k];
}

ll modulo(ll x, ll m) {
	return ((x%m)+m)%m;
}

//finds the inverse of a mod m. It is required that a is coprime to m.
ll invert(ll a, ll m) {
	ll x, y;	gcd(a, m, x, y);
	return modulo(x, m);
}

//finds c modulo m*n such that c is a mod m and b mod n. Requires that m and n are comprime.
ll ch_rem(ll a, ll m, ll b, ll n) {
	return modulo(a + m * modulo((b-a)*invert(m, n), n), m*n);
}

int main() {
	srand(time(0));

	ll x1, x2, x3, y1, y2, y3, m1, m2, m3,z;
	cin >> m1 >> m2 >> m3 >> x1 >> x2 >> x3 >> y1 >> y2 >> y3;
	if(y1*y2*y3 < 1000) { //ADJUST
		for(z=0;;++z) {
			if(dist(z % m1, x1, m1) <= y1 &&
				 dist(z % m2, x2, m2) <= y2 &&
				 dist(z % m3, x3, m3) <= y3)
				break;
		}
	} else {
		z = m1*m2*m3;
		for(int t1 = -y1; t1 <= y1; ++t1)
		for(int t2 = -y2; t2 <= y2; ++t2)
		for(int t3 = -y3; t3 <= y3; ++t3) {
			z = min(z,
								ch_rem(
								ch_rem(modulo(x1+t1, m1), m1,
											 modulo(x2+t2, m2), m2), m1*m2,
											 modulo(x3+t3, m3), m3));
		}
	}
	cout << z << endl;
}
