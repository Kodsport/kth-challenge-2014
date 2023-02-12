#include <iostream>
using namespace std;

int n;

double f(int);
double g(int);
double h(int,int);

double dpf[2010];
double f(int m) {
  double& x=dpf[m];
  if(x!=-1) return x;
  if (m>=n) return x = 1;
  return x = f(m+1)*(n-m)/(n-1) + g(m)*(m-1)/(n-1);
}

double dpg[2010];
double g(int m) {
  double& x=dpg[m];
  if(x!=-1) return x;
  if (m>=n) return x = 1;
  return x = g(m+1)*m/(n-1) + h(m,m+2)*(n-m-1)/(n-1);
}

double dph[2010][2010];
double h(int a, int m) {
  double& x=dph[a][m];
  if (m>n) return x = 0;
  return x = g(m)*a/(n-1) + h(a,m+1)*(n-m)/(n-1);
}
    

int main() {
  cin >> n;
  for (int i=0;i<2010;++i) dpf[i]=-1;
  for (int i=0;i<2010;++i) dpg[i]=-1;
  for (int i=0;i<2010;++i) for (int j=0;j<2010;++j) dph[i][j]=-1;
  printf("%.15f\n",f(2));
}
