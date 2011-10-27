#include <iostream>

using namespace std;

unsigned int dp[101][101];
bool wolf[101][101];


int main(){
  int w, h;
  while (cin >> w >> h && w && h){
    for (int i=0; i<=w; ++i){
      for (int j=0; j<=h; ++j){
        dp[i][j] = wolf[i][j] = 0;
      }
    }
    int wolves;
    cin >> wolves;
    while (wolves--){
      int i, j;
      cin >> i >> j;
      wolf[i][j] = true;
    }

    dp[0][0] = 1;
    for (int i=0; i<=w; ++i){
      for (int j=0; j<=h; ++j){
        if (!wolf[i][j]){
          if (i > 0) dp[i][j] += dp[i-1][j];
          if (j > 0) dp[i][j] += dp[i][j-1];
        }
      }
    }

    int t = dp[w][h];
    if (t == 0){
      cout << "There is no path." << endl;
    }else{
      cout << "There ";
      if (t == 1) cout << "is one path";
      else cout << "are " << t << " paths";
      cout << " from Little Red Riding Hood's house to her grandmother's house." << endl;
    }

  }
  return 0;
}
