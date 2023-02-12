#include <cstdio>
#include <map>
#include <vector>
#include <string>

using namespace std;

bool debug = false;
#define dprintf debug && printf

typedef vector<int> vi;

int val[500], bias[500];
vi clauses[10000];

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

int main(void) {
	int N;
	scanf("%d", &N);
	for (int i = 0; i < N; ++i) {
		int w;
		scanf("%d", &w);
		dprintf("read clause width %d\n", w);
		for (int j = 0; j < w; ++j) {
			clauses[i].push_back(get_topping());
			bias[abs(clauses[i].back())] += sgn(clauses[i].back());
		}
	}
	for (int i = 1; i <= topname.size(); ++i) val[i] = sgn(bias[i]);
	for (int i = 1; i <= topname.size(); ++i)
		if (val[i] > 0)
			printf("%s\n", topname[i-1].c_str());
	return 0;
}

