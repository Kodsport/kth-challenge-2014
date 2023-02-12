#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
using namespace std;

typedef unordered_map<string,int> HSI;
typedef vector<string> VS;
typedef vector<int> VI;
typedef unordered_set<int> HI;
typedef vector<VI> VVI;

int main() {
  HSI dict;
  VS idict;
  VVI csp;
  VVI has;
  int N;
  cin >> N;
  for (int i=0; i<N; ++i) {
    int w;
    cin >> w;
    csp.push_back({});
    csp.back().reserve(w);
    for (int j=0; j<w; ++j) {
      string s;
      cin >> s;
      bool polarity = (s[0]=='+');
      s = s.substr(1);
      if (not dict.count(s)) {
        dict[s]=idict.size();
        idict.push_back(s);
        has.push_back({});
        has.push_back({});
      }
      int l = (dict[s]<<1) | (polarity?1:0);
      csp.back().push_back(l);
      has[l].push_back(i);
    }
  }
  VI a(idict.size());
  for (int& x : a) x=rand()&1;
  VI fals(N);
  for (int i=0; i<N; ++i) {
    for (int l : csp[i]) {
      int x = l >> 1;
      fals[i] += ((l^a[x])&1);
    }
  }
  HI unsat;
  for (int i=0; i<N; ++i) {
    int w = csp[i].size();
    int sat = w - fals[i];
    if (sat * 3 <= w) unsat.insert(i);
  }
  while(not unsat.empty()) {
    int i = rand()%unsat.size();
    auto it = unsat.begin();
    for (int j=0; j<i; ++j,++it);
    VI flip;
    for (int l : csp[*it]) {
      int x = l >> 1;
      if ((l^a[x])&1) flip.push_back(x);
    }
    int j = rand()%flip.size();
    a[flip[j]]^=1;
    int l = (flip[j]<<1) | a[flip[j]];
    for (int i : has[l]) {
      fals[i]--;
      int w = csp[i].size();
      int sat = w - fals[i];
      if (sat * 3 > w) unsat.erase(i);
    }
    for (int i : has[l^1]) {
      fals[i]++;
      int w = csp[i].size();
      int sat = w - fals[i];
      if (sat * 3 <= w) unsat.insert(i);
    }
  }
  for (int j=0; j<idict.size(); ++j) {
    if (a[j]) cout << idict[j] << endl;
  }
}
