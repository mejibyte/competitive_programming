#include <iostream>
#include <map>
using namespace std;

/* Union find */
const int NN = 100005;
int p[NN], rank[NN];
void make_set(int x){ p[x] = x, rank[x] = 0; }
void link(int x, int y){ rank[x] > rank[y] ? p[y] = x : p[x] = y, rank[x] == rank[y] ? rank[y]++: 0; }
int find_set(int x){ return x != p[x] ? p[x] = find_set(p[x]) : p[x]; }
void merge(int x, int y){ link(find_set(x), find_set(y)); }
/* End union find */

int f[NN]; 

int main(){
  int t;
  cin >> t;
  while (t--){
    for (int i=0; i<NN; ++i) make_set(i), f[i] = 1;

    int curID = 0;
    map<string, int> id;
    int e;
    cin >> e;
    while (e--){
      string s, t;
      cin >> s >> t;
      int a, b;
      if (id.count(s)) a = id[s];
      else a = id[s] = curID++;
      if (id.count(t)) b = id[t];
      else b = id[t] = curID++;

      int i, j;
      if ((i = find_set(a)) == (j = find_set(b))){
	cout << f[i] << endl;
      }else{
	int all = f[i] + f[j];
	merge(a, b);
	f[find_set(a)] = all;
	cout << all << endl;
      }
    }
  }
  return 0;
}
