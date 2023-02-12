#include <cstdio>
#include <map>
#include <vector>
#include <string>

using namespace std;

bool debug = false;
#define dprintf debug && printf

typedef vector<int> vi;

int val[500], satlits[10000];
vi clauses[10000], occ[2][500];
vi unsat;

bool good(int sat, int width) {
	return 3*sat >= 2*width || 3*(sat-1) > width;
}

int abs(int v) { return v < 0 ? -v : v; }

int unsatvar(int C) {
	while (true) {
		int v = clauses[C][random() % clauses[C].size()];
		if (v*val[abs(v)] < 0) {
			dprintf("unsatvar %d = %d\n", C, v);
			return abs(v);
		}
	}
}

void flip(int v) {
	val[v] = -val[v];
	for (auto C: occ[(1+val[v])/2][v]) {
		++satlits[C];
	}
	for (auto C: occ[(1-val[v])/2][v]) {
		--satlits[C];
		if (!good(satlits[C], clauses[C].size()) &&
			good(satlits[C]+1, clauses[C].size()))
			unsat.push_back(C);
	}
}

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

int main(void) {
	int N;
	scanf("%d", &N);
	for (int i = 0; i < N; ++i) {
		int w;
		scanf("%d", &w);
		dprintf("read clause width %d\n", w);
		satlits[i] = 0;
		for (int j = 0; j < w; ++j) {
			clauses[i].push_back(get_topping());
			if (clauses[i][j] > 0) {
				occ[1][clauses[i][j]].push_back(i);
			} else {
				++satlits[i];
				occ[0][-clauses[i][j]].push_back(i);
			}
		}
		if (!good(satlits[i], clauses[i].size())) unsat.push_back(i);
	}
	dprintf("%d vars, %d clauses, init %d unsat\n",
		   topname.size(), N, unsat.size());
	for (int i = 1; i <= topname.size(); ++i) val[i] = -1;
	
	while (!unsat.empty()) {
		int C = unsat.back(); unsat.pop_back();
		dprintf("fix clause %d\n", C);
		while (!good(satlits[C], clauses[C].size()))
			flip(unsatvar(C));
	}

	for (int i = 1; i <= topname.size(); ++i)
		if (val[i] > 0)
			printf("%s\n", topname[i-1].c_str());
	return 0;
}
