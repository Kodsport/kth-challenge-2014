#include <cstdio>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;

bool debug = false;
#define dprintf debug && printf

typedef vector<int> vi;

int V;
int val[500], bias[500], occs[500], idx[500];
int unsatlits[10000];
vi cocc[2][500];
vector<vi> clauses;

int abs(int v) { return v < 0 ? -v : v; }
int sgn(int v) { return v < 0 ? -1 : 1; }

vector<string> topname;
map<string, int> topidx;

int get_topping() {
	char str[100];
	scanf("%s", str);
	if (!topidx[str+1])	{
		topidx[str+1] = topidx.size();
		topname.push_back(str+1);
	}
	return (*str == '+' ? 1 : -1)*topidx[str+1];
}

bool search(int i) {
	if (i < 0) return true;
	int v = idx[i];
	for (int b = 1; b >= -1; b -= 2) {
		val[v] = b*sgn(bias[v]);
		bool ok = true;
		//		printf("%*stry %d <- %d\n", 2*(topname.size()-1-i), "", v, val[v]);
		for (int C: cocc[(1-val[v])/2][v]) {
			++unsatlits[C];
			if (3*unsatlits[C] >= 2*clauses[C].size()) ok = false;
		}
		if (ok && search(i-1)) return true;
		for (int C: cocc[(1-val[v])/2][v]) {
			--unsatlits[C];
			if (3*unsatlits[C] >= 2*clauses[C].size()) ok = false;
		}
	}
	return false;
}

int main(void) {
	int N;
	scanf("%d", &N);
	clauses.resize(N);
	for (int i = 0; i < N; ++i) {
		int w;
		scanf("%d", &w);
		dprintf("read clause width %d\n", w);
		unsatlits[i] = 0;
		for (int j = 0; j < w; ++j) {
			int l = get_topping();
			clauses[i].push_back(l);
			bias[abs(l)] += sgn(l);
			++occs[abs(l)];
			cocc[(1+sgn(l))/2][abs(l)].push_back(i);
		}
	}
	for (int i = 0; i < topname.size(); ++i) idx[i] = i+1;
	sort(idx, idx+topname.size(), 
		 [](int a, int b) { return abs(bias[a])*occs[b] < abs(bias[b])*occs[a]; });

	assert(search(topname.size()-1));

	for (int i = 1; i <= topname.size(); ++i)
		if (val[i] > 0)
			printf("%s\n", topname[i-1].c_str());
	return 0;
}

