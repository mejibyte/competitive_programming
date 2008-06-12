#include <iostream>
#include <vector>

using namespace std;

int pos[10], m[10], C, best, S;

void backtrack(vector<int> &n){
  for (int i=0, sum = 0; i<S; ++i){
    sum += n[i];
    if (sum > C) return;
  }

  int mask = 0;
  for (int i=0; i<S; ++i){
    if (n[i] > 0){
      for (int j=pos[i]-n[i]; j<= pos[i]+n[i]; ++j){
	mask = mask | (1<<j);
      }
    }
  }
  
  best >?= __builtin_popcount(mask);

  for (int i=0; i<S; ++i){
    if (n[i]+1 <= m[i]){
      n[i]++;
      backtrack(n);
      n[i]--;
    }
  }
}

int main(){
  int T;
  cin >> T;
  while (T--){
    int L;
    cin >> L >> S;
    for (int i=0; i<S; ++i){
      cin >> pos[i];
    }
    cin >> C;
    for (int i=0; i<S; ++i){
      cin >> m[i];
    }

    best = -1;
    vector<int> n(S, 0);
    backtrack(n);
    cout << best << endl;
    
  }
  return 0;
}
