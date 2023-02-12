#include <iostream>
using namespace std;

typedef long long ll;

ll euclid(ll a, ll b, ll &x, ll &y) {
	if (b) {
		ll d = euclid(b, a%b, y, x);
		return y -= a/b*x, d;
	}
	return x=1, y=0, a;
}
ll mod(ll x, ll m) {
	return ((x%m)+m)%m;
}
ll chinese(ll a, ll m, ll b, ll n) {
	ll x,y;
	euclid(m,n,x,y);
	// ll ret = (a*(y+m)%m*n + b*(x+n)%n*m + m*n)%(m*n);
	ll ret = mod(a+m*mod((b-a)*x,n),m*n);
	return ret;
}
ll chinese(ll a, ll m, ll b, ll n, ll c, ll o) {
	return chinese(chinese(a, m, b, n), m*n, c, o);
}

int main() {
	ll m1,m2,m3,x1,x2,x3,y1,y2,y3;
	cin >> m1 >> m2 >> m3 >> x1 >> x2 >> x3 >> y1 >> y2 >> y3;
	ll best = m1*m2*m3;
	for (int d1 = -y1; d1 <= y1; ++d1) {
		for (int d2 = -y2; d2 <= y2; ++d2) {
			for (int d3 = -y3; d3 <= y3; ++d3) {
				if (d3 > -y3 && d1 > -y1 && d2 > -y2)
					break;
				best = min(best, chinese((x1+d1+m1)%m1,m1, (x2+d2+m2)%m2,m2, (x3+d3+m3)%m3,m3));
			}
		}
	}
	cout << best << endl;
}