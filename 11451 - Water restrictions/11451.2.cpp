#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

int pos[10], m[10], n[10], C, best, S;

//int cantidad = 0;

void backtrack(){
  //cantidad++;

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
      backtrack();
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
    assert(C <= 11);
    for (int i=0; i<S; ++i){
      cin >> m[i];
    }

    best = -1;
    //cantidad = 0;
    for (int i=0; i<S; ++i){
      n[i] = 0;
    }
    //backtrack();
    cout << best << endl;
    //cout << "Evalué " << cantidad << " opciones.\n";
    
  }
  return 0;
}
