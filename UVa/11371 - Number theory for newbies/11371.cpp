#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

using namespace std;

int main(){
  string s;
  while (getline(cin, s)){
    assert(s[0] != '0');
    vector<int> v(s.size());
    for (int i=0; i<s.size(); ++i) v[i] = s[i] - '0';
    sort(v.begin(), v.end(), greater<int>() );
    
    long long int a = 0;
    for (int i=0; i<v.size(); ++i){
      a*= 10; a += v[i];
    }

    sort(v.begin(), v.end());
    if (v[0] == 0)
      for (int i=1; i<v.size(); ++i){
	if (v[i] != 0){
	  swap(v[0], v[i]);
	  break;
	}
      }
    
    long long int b = 0;
    for (int i=0; i<v.size(); ++i){
      b*= 10; b += v[i];
    }

    printf("%lld - %lld = %lld = 9 * %lld\n", a, b, a-b, (a-b)/9);
    
  }
  return 0;
}
