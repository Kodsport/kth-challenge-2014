#include <cstdio>
#include <map>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

bool debug = false;
#define dprintf debug && printf

typedef vector<int> vi;

int val[500], bias[500];
int unsats[10000], V;
vi occs[2][500];
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

bool set(int var, int b) {
	val[var] = b;
	for (int c: occs[(1-b)/2][var]) {
		int w = clauses[c].size(), t = w/3+1;
		++unsats[c];
		if (unsats[c] > w-t) return false;
		if (unsats[c] == w-t) {
			for (int w: clauses[c])
				if (!val[abs(w)] && !set(abs(w), sgn(w)))
					return false;
		}
	}
	return true;
}

bool ppz() {
	int var[500];
	for (int i = 0; i < V; ++i)
		var[i] = i+1, val[i+1] = 0;
	memset(unsats, 0, sizeof(unsats));
	random_shuffle(var, var+V);
	fprintf(stderr, "GO PPZ\n");
	for (int i = 0; i < V; ++i) {
		int v = var[i];
		if (val[v]) continue;
		if (!set(v, 1 - 2*(random() % 2))) return false;
	}
	return true;
}

int main(void) {
	int N;
	scanf("%d", &N);
	srandom(42);
	clauses.resize(N);
	for (int i = 0; i < N; ++i) {
		int w;
		scanf("%d", &w);
		dprintf("read clause width %d\n", w);
		for (int j = 0; j < w; ++j) {
			int v = get_topping();
			clauses[i].push_back(v);
			bias[abs(v)] += sgn(v) > 0;
			occs[(1+sgn(v))/2][abs(v)].push_back(i);
		}
	}
	V = topname.size();
	while (!ppz()); 
	for (int i = 1; i <= topname.size(); ++i)
		if (val[i] > 0)
			printf("%s\n", topname[i-1].c_str());
	return 0;
}

