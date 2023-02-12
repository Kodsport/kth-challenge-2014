#include <cstdio>
#include <vector>
#include <set>
#include <cstring>

using namespace std;
typedef long long ll;
typedef pair<int,ll> pil;
typedef vector<pil> vpil;

const ll MOD = 1784831789LL;

vpil adj[2][200000];
ll dist[2][200000];
ll paths[2][200000];
int s[2];

ll Paths(int dir, int u) {
	if (u == s[dir]) return 1;
	ll &r = paths[dir][u];
	if (r == -1) {
		r = 0;
		for (pil p: adj[1-dir][u])
			if (dist[dir][p.first] == dist[dir][u]-p.second)
				(r += Paths(dir, p.first)) %= MOD;
	}
	return r;
}

int main(void) {
	int N, M;
	scanf("%d%d", &N, &M);
	for (int i = 0; i < M; ++i) {
		int u, v, w;
		scanf("%d%d%d", &u, &v,&w);
		adj[0][u].push_back(pil(v, w));
		adj[1][v].push_back(pil(u, w));
	}
	scanf("%d%d", s, s+1);
	memset(dist, 0x1f, sizeof(dist));
	memset(paths, -1, sizeof(paths));
	for (int d = 0; d < 2; ++d) {
		dist[d][s[d]] = 0;
		set<pil> q;
		q.insert(pil(0, s[d]));
		while (!q.empty()) {
			int u = q.begin()->second;
			q.erase(q.begin());
			for (pil n: adj[d][u]) {
				ll nd = dist[d][u] + n.second;
				if (dist[d][n.first] > nd) {
					q.erase(pil(dist[d][n.first], n.first));
					q.insert(pil(dist[d][n.first] = nd, n.first));
				}
			}
		}
	}
	for (int i = 0; i < N; ++i) {
		if (dist[0][i] + dist[1][i] == dist[0][s[1]] &&
			Paths(0, i)*Paths(1, i) % MOD == Paths(0, s[1]))
			printf("%d\n", i);
	}
	return 0;
}
