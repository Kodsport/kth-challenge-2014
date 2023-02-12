//Solution by lukasP (Lukáš Poláček)
#include <iostream>
#include <string>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)

int main()
{
    int h;
    cin >> h;
    string s;
    cin >> s;

    int num = 1;
    rep(i,0,s.size())
        num = num * 2 + (s[i] == 'R');
    cout << ((1 << (h + 1)) - num) << endl;
}
