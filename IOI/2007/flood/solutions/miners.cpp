#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MAX=100005;

int n;
char s[MAX+1];
int dp[2][4][4][4];

void read_input() {
  scanf("%d\n", &n);
  fgets(s, MAX+1, stdin);
  for (int i = 0; i < n; i++)
    if (s[i] == 'F')
      s[i] = 1;
    else if (s[i] == 'M')
      s[i] = 2;
    else
      s[i] = 3;
}

inline int ore (int a, int b, int c) {
  int sol = 0;
  if (a == 1 || b == 1 || c == 1) sol++;
  if (a == 2 || b == 2 || c == 2) sol++;
  if (a == 3 || b == 3 || c == 3) sol++;
  return sol;
}

int main() {
  read_input();

  int now = 0, prev = 1;
  for ( int k=n-1; k>=0; --k ) {
     for ( int a=0; a<=3; ++a ) {
        for ( int b=0; b<=3; ++b ) {
           for ( int c=0; c<=3; ++c ) {
              int left = ore(s[k], s[k-1], a) + dp[prev][s[k-1]][b][c];
              int right = ore(s[k], b, c) + dp[prev][b][s[k-1]][a];
              dp[now][a][b][c] = max(left, right);
           }
        }
     }

     swap(now, prev);
  }
  printf("%d\n", dp[prev][0][0][0]);
  return 0;
}
