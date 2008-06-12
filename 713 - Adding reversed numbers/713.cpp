#include <vector>
#include <iostream>
#include <algorithm>


using namespace std;

int main(){
  int S;
  cin >> S;
  while (S--){
    string s, t, r="";
    cin >> s >> t;
    while (s.size() > 1 && s[s.size()-1] == '0') s.erase(s.size()-1);
    while (t.size() > 1 && t[t.size()-1] == '0') t.erase(t.size()-1);
    int n = max(s.size(), t.size());
    int carry = 0;
    for (int i=0; i<n; ++i){
      int x = carry;
      if (i < s.size()){
	x += s[i] - '0';
      }
      if (i < t.size()){
	x += t[i] - '0';
      }
      carry = x/10;
      x %= 10;
      r += x + '0';
    }
    if (carry) r += carry + '0';
    while (r.size() > 1 && r[0] == '0'){
      r.erase(0, 1);
    }
    cout << r << endl;
  }

  return 0;
}
