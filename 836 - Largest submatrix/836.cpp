#include <iostream>
#include <vector>

using namespace std;

int main(){
  int C;
  cin >> C;
  string line;
  getline(cin, line);
  getline(cin, line);
  for (int c=0; c<C; c++){
    if (c > 0) cout << endl;
    vector<string> m;
    while (getline(cin, line) && line != ""){
      m.push_back("0" + line);
    }
    int n = m.size();
    m.insert(m.begin(), string(n+1, '0'));

    /*
      dp[i][j] = suma de la matriz que va desde la esquina (0,0) hasta la esquina (i,j)
     */
    int dp[n+1][n+1];
    for (int i=0; i<=n; ++i)
      for (int j=0; j<=n; ++j)
        dp[i][j] = m[i][j] - '0';

    for (int i=1; i<=n; ++i)
      for (int j=1; j<=n; ++j)
        dp[i][j] += dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1];

    int answer = 0;
    for (int i=1; i<=n; ++i)
      for (int j=1; j<=n; ++j)
        for (int a=i; a<=n; ++a)
          for (int b=j; b<=n; ++b){
            if ( ( dp[a][b] - dp[a][j-1] - dp[i-1][b] + dp[i-1][j-1] ) == (a - i + 1)*(b - j + 1) ){
              answer = max(answer, (a-i+1)*(b-j+1));
            }
          }

    cout << answer << endl;


  }
  return 0;
}
