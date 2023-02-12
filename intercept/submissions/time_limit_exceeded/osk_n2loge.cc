#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include <cassert>

using namespace std;

typedef long long LL;
typedef pair<int,int> PII;

const LL INF = 1LL<<62;

int N, M;

LL dijkstra(const int skip, const LL opt_out, const vector<vector<PII> > &neigh, const int s, const int t) {
    set<pair<LL, int> > q;
    vector<LL> dist(N, INF);
    q.insert(make_pair(0LL, s));
    dist[s] = 0;
    while (!q.empty()) {
        pair<LL, int> cur = *q.begin();
        q.erase(q.begin());
        if (cur.second == skip) continue;
        if (cur.first > opt_out) continue;
        for (int i = 0; i < neigh[cur.second].size(); ++i) {
            const PII &edge = neigh[cur.second][i];
            LL nextDist = cur.first + edge.second;
            int nextNode = edge.first;
            if (nextDist < dist[nextNode]) {
                if (nextNode == skip) continue;
                if (nextDist > opt_out) continue;
                // update and replace
                LL tempDist = dist[nextNode];
                dist[nextNode] = nextDist;
                
                set<pair<LL, int> >::iterator it = q.find(make_pair(tempDist, nextNode));
                if (it != q.end()) {
                    q.erase(it);
                }

                q.insert(make_pair(nextDist, nextNode));
            }
        }
    }
    return dist[t];
}


int main() {
    cin >> N >> M;
    vector<vector<PII> > neigh(N, vector<PII>());
    for (int i = 0; i < M; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        neigh[u].push_back(make_pair(v,w));
    }
    int s,t;
    cin >> s >> t;
    LL opt = dijkstra(-1, INF, neigh, s, t); 
    for (int i = 0; i < N; ++i) {
        LL new_opt = dijkstra(i, opt, neigh, s, t);
        //cout << "optimal dist is " << new_opt << endl;
        if (new_opt > opt) cout << i << " ";
    }
    cout << endl;
}
