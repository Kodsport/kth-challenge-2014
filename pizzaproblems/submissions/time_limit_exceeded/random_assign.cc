#include <cstdio>
#include <map>
#include <vector>
#include <string>

using namespace std;

bool debug = false;
#define dprintf debug && printf

typedef vector<int> vi;

int val[500];
vector<vi> clauses;

int abs(int v) { return v < 0 ? -v : v; }

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
		clauses.push_back(vi());
		for (int j = 0; j < w; ++j)
			clauses[i].push_back(get_topping());
	}
	while (true) {
		for (int i = 1; i <= topname.size(); ++i) {
			val[i] = random()%2 * 2 - 1;
		}
		bool ok = true;
		for (auto &C: clauses) {
			int s = 0;
			for (auto &l: C)
				s += (l*val[abs(l)] > 0);
			ok &= (3*s > C.size());
			if (!ok) break;
		}
		if (ok) break;
	}

	for (int i = 1; i <= topname.size(); ++i)
		if (val[i] > 0)
			printf("%s\n", topname[i-1].c_str());
	return 0;
}
