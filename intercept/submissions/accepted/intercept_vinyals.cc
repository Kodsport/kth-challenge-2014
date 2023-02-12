#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cassert>
using namespace std;

typedef long long ll;
typedef pair<ll,int> PII;
typedef vector<PII> VP;
typedef vector<VP> VVP;
typedef vector<ll> VL;
typedef vector<int> VI;
typedef vector<VI> VVI;

const ll INF=1ll<<61;

VI parent;
VI uni;
VVI h;

void clear(int u, int last) {
  while(true) {
    assert(u>=0);
    u=parent[u];
    if (u==last) break;
    uni[u]=false;
  }
}

void articulation(int u, int last) {
  static bool first=true;
  for (auto it:h[u]) {
    if (parent[it]==u) continue;
    if (parent[it]!=-1) {
      clear(it,last);
      uni[u]=false;
    }
    else {
      parent[it]=u;
      uni[it]=first;
      articulation(it,uni[u]?u:last);
    }
    first=false;
  }
}

void dijkstra(const VVP& g, int s) {
  int n=g.size();
  VL distance(n,INF);
  h=VVI(n);
  priority_queue<PII,vector<PII>,greater<PII>> q;
  distance[s]=0;
  q.push(PII(0,s));
  while(!q.empty()) {
    ll d=q.top().first;
    int u=q.top().second;
    q.pop();
    for (auto it:g[u]) {
      ll d2=d+it.first;
      int v=it.second;
      if (distance[v]==d2) {
        h[v].push_back(u);
      }
      else if (distance[v]>d2) {
        h[v].assign({u});
        distance[v]=d2;
        q.push(PII(d2,v));
      }
    }
  }
}

int main() {
  int n,m;
  cin >> n >> m;
  VVP g(n);
  for (int i=0;i<m;++i) {
    int u,v,w;
    cin >> u >> v >> w;
    g[u].push_back(PII(w,v));
  }
  int s,t;
  cin >> s >> t;
  dijkstra(g,s);
  parent=VI(n,-1);
  uni=VI(n,false);
  uni[t]=true;
  articulation(t,-1);
  bool first=true;
  for (int i=0;i<n;++i) {
    if(uni[i]) {
      if (!first) cout << ' ';
      first=false;
      cout << i;
    }
  }
  cout << endl;
}
