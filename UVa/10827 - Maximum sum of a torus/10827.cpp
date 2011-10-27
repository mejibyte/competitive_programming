#include <iostream>
#include <vector>

using namespace std;

int main(){
  int runs;
  scanf("%d", &runs);
  while (runs--){
    int n;
    cin >> n;
    int m[n][n];
    for (int i=0; i<n; ++i){
      for (int j=0; j<n; ++j){
        scanf("%d", &m[i][j]);
      }
    }

    int answer = 0;
    for (int i=0; i<n; ++i){
      vector<int> r(n, 0);
      int j = i;
      do{
        for (int k=0; k<n; ++k){
          r[k] += m[j][k];
        }

        int sum = 0;
        for (int k=0; k<n; ++k){
          sum += r[k];
          if (sum > answer) answer = sum;
          if (sum < 0) sum = 0;
        }

        sum = 0;
        int a = 0, b = 0;
        for (int k=0; k<n; ++k){
          sum += r[k];
          b += r[k];
          a = min(a, b);
          if (b > 0) b = 0;
        }
        if (sum - a > answer) answer = sum - a;
        j = (j+1)%n;
      }while(j != i);
    }
    printf("%d\n", answer);
  }
  return 0;
}
