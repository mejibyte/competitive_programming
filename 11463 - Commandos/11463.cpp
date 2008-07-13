#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 100;

unsigned int g[MAXN][MAXN];

int main(){
  int T;
  cin >> T;
  for (int C=1; C <= T; C++){
    int n;
    cin >> n;

    for (int i=0; i<n; ++i){
      for (int j=0; j<n; ++j){
        g[i][j] = INT_MAX;
      }
      g[i][i] = 0;
    }

    int R;
    cin >> R;
    while (R--){
      int i, j;
      cin >> i >> j;
      g[i][j] = g[j][i] = 1;
    }
    int start, end;
    cin >> start >> end;

    for (int k=0; k<n; ++k){
      for (int i=0; i<n; ++i){
        for (int j=0; j<n; ++j){
          g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
        }
      }
    }

    unsigned int answer = 0;
    for (int i=0; i<n; ++i){
      answer = max(answer, g[start][i] + g[i][end]);
    }

    cout << "Case " << C << ": " << answer << endl;
  }
  return 0;
}
