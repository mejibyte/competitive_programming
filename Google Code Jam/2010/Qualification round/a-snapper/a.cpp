#include <iostream>
using namespace std;


bool f(long long n, long long k){
  for (int i = 0; i < n; ++i){
    if (!( k & (1LL << i) )) return false;
  }
  return true;
}

void solve(){
  long long n, k;
  cin >> n >> k;
  printf("%s\n", f(n, k) ? "ON" : "OFF");
}

int main(){
  int T;
  cin >> T;
  for (int c = 1; c <= T; ++c){
    printf("Case #%d: ", c);
    solve();
  }
}
