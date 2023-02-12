#include <cstdio>
#include <cstring>
#include <set>

typedef long long ll;
const ll oo = 0x1f1f1f1f1f1f1f1fLL;

ll mod(ll x, ll m) { return (x%m+m)%m; }
ll egcd(ll a, ll b, ll &x, ll &y) {
	if (b == 0) return x = 1, y = 0, a;
	egcd(b, a % b, y, x);
	y -= a/b*x;
	return a*x + b*y;
}
ll lcm(ll a, ll b) { ll x, y; return a/egcd(a,b, x, y)*b; }

ll crt(ll a1, ll m1, ll a2, ll m2) {
	ll z1, z2;
	ll d = egcd(m1, m2, z1, z2);
	if (d > 1) return (a2-a1)%d ? oo : mod(m1/d*z1*mod(a2-a1, m2)+a1, m1/d*m2);
	return mod(a1*z2*m2 + a2*z1*m1, m1*m2);
}

ll exact[1000000];

void apxlin(ll c, ll m, ll err, ll *sol) {
	memset(exact, 0x1f, sizeof(exact));
	for (int k = 0, x = 0; exact[x] > k; (x += c) %= m, ++k)
		exact[x] = k;
	std::set<int> B;
	for (int i = -err; i <= err; ++i) 
		if (exact[(m+i)%m] < oo) B.insert(exact[(m+i)%m]);
	for (int x = 0; x < m; ++x) {
		sol[x] = B.empty() ? oo : *B.begin();
		if (2*err >= m-1) sol[x] = 0;
		if (exact[(m+x-err)%m] < oo) B.erase(exact[(m+x-err)%m]);
		if (exact[(m+x+err+1)%m] < oo) B.insert(exact[(m+x+err+1)%m]);
	}
}

int main(void) {
	ll m1, m2, m3, x1, x2, x3, y1, y2, y3;
	scanf("%lld%lld%lld%lld%lld%lld%lld%lld%lld",
		  &m1, &m2, &m3, &x1, &x2, &x3, &y1, &y2, &y3);
	ll m12 = lcm(m1, m2), r = oo, fin[1000000];
	apxlin(m12 % m3, m3, y3, fin);
	for (int e1 = -y1; e1 <= y1; ++e1)
		for (int e2 = -y2; e2 <= y2; ++e2) {
			ll t = crt(x1+e1, m1, x2+e2, m2);
			if (t == oo) continue;
			ll k = fin[mod(x3-t, m3)];
			if (k < oo) r = std::min(r, t+k*m12);
		}
	printf("%lld\n", r);

	return 0;
}
