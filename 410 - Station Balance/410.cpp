using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <fstream>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <deque>
#include <stack>
#include <map>
#include <set>

//_for(i, a, b):  a <= i < b
#define _for(i, a, b) for (int i=a, _n = b; i<_n; ++i)
//_from(i, a, b): a > i >= b
#define _from(i, a, b) for (int i=a-1, _n = b; i>=_n; --i)
 
#define D(x) cout << #x " is " << x << endl

struct state{
  int used, chamber, sum;
  state(){}
  state(int used, int i, int s) : used(used), chamber(i), sum(s){}

  bool operator <(const state &that) const {
    return sum > that.sum || (sum == that.sum && chamber < that.chamber);
  }
};

const int oo =  INT_MAX / 4;
int p[10];
int d[1<<11][6], choice[1<<11][6];

#define enqueue(new_used, new_i, new_w, c)	\
  if (new_w < d[new_used][new_i]){		\
    d[new_used][new_i] = new_w;			\
    choice[new_used][new_i] = c;		\
    q.push(state(new_used, new_i, new_w));	\
    if (0) printf("   pushed used=%x, i=%d, w=%d\n", new_used, new_i, new_w); \
  }

int binary(int i){
  for (unsigned int mask = 1 << 10; mask; mask >>= 1){
    cout << (i & mask ? "1" : "0");
  }
}
    

int main(){

  int n, m, i, j, k, Set = 1;
  while (cin >> n >> m){
    int mass = 0;
    for (i=0; i<m; ++i)
      cin >> p[i], mass += p[i];

    for (i=0; i<(1<<m); ++i)
      for (j=0; j<=n; ++j)
	d[i][j] = oo;

    priority_queue<state> q;
    q.push(state(0, 0, 0));
    while (q.size()){
      int used = q.top().used;
      int i = q.top().chamber;
      int w = q.top().sum;


      /*
      printf("popped used=%x, i=%d, w=%d\n", used, i, w);
      binary(used);
      printf("\n");
      */

      q.pop(); //!

      if (i == n && used == (1 << m) - 1){
	//Solved!
	printf("Set #%d\n", Set++);

	

	int mask = used;

	for (j=n; j>0; --j){
	  printf("%2d:", n-j);

	  for (k=0; k<m; ++k){
	    if (choice[mask][j] & (1 << k)) printf(" %d", p[k]);
	  }
	  printf("\n");

	  mask &= ~choice[mask][j];
	}

	printf("IMBALANCE = %.5lf\n\n", 1.0 * w / n);
	break;
      }

      if (i > n || w > d[used][i]) continue;

      enqueue(used, i+1, w + mass, 0);
      for (j=0; j<m; ++j){
	if ( ! (used & (1 << j)) ){
	  int w_extra = abs(n*p[j] - mass);
	  enqueue(used | (1 << j), i+1, w + w_extra, (1 << j));

	  for (k=0; k<m; ++k)
	    if (k != j && ( ! (used & (1 << k)) )){
	      w_extra  = abs(n*(p[j]+p[k]) - mass);
	      enqueue(used | (1 << j) | (1 << k), i+1, w + w_extra, (1 << j) | (1 << k));
	    }
	}
      }
    }
    
  }

  return 0;
}
