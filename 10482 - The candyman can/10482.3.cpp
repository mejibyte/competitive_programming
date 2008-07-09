/*
  Problem: 10482 - The Candyman can
  (UVa Online Judge)

  Andrés Mejía-Posada

  ¡Accepted!
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int SIZE = 40, MAXN = 32;

/*
  dp[i][a][b] = verdadero si puedo repartir las primeras
  i monedas en tres grupos tales que el grupo con mayor peso
  tenga a unidades más que el grupo con menos peso & el grupo
  de la mitad tenga b unidades más que el grupo con menos peso
 */
bool dp[MAXN][SIZE+1][SIZE+1];

int main(){
  int Casos;
  cin >> Casos;
  for (int C=1; C<=Casos; C++){
    int n, sum = 0;
    cin >> n;
    vector<int> w(n);
    for (int i=0; i<n; ++i){
      cin >> w[i];
      sum += w[i];
    }

    sum = min(sum, SIZE);

    for (int i=0; i<n; ++i)
      for (int a=0; a<=sum; ++a)
        for (int b=0; b<=sum; ++b)
          dp[i][a][b] = false;

    cout << "Case " << C << ": ";
    //cout << "Sum: " << sum << endl;


    dp[0][w[0]][0] = true;
    for (int i=0; i<n-1; ++i)
      for (int a=0; a<=sum; ++a)
        for (int b=0; b<=sum; ++b)
          if (dp[i][a][b])
            for (int j=0; j<3; ++j){
              vector<int> t(3);
              t[0] = a, t[1] = b, t[2] = 0;
              t[j] += w[i+1];
              sort(t.begin(), t.end());
              if (t[2] - t[0] <= sum){
                dp[i+1][t[2] - t[0]][t[1] - t[0]] = true;
              }
            }

    int answer = -1;
    for (int a=0; a<=sum && answer == -1; ++a)
      for (int b=0; b<=a && answer == -1; ++b)
        if (dp[n-1][a][b]){
          answer = a;
        }

    cout << answer << endl;
    if (answer == -1) while (true) cout << "error ";

  }
  return 0;
}


