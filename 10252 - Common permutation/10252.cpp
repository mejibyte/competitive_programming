#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>
using namespace std;

int main(){
  string s,t;
  while (getline(cin, s) && getline(cin, t)){
    //assert(s.find(" ") != string::npos);
    //assert(s.length() > 0 && t.length() > 0);
    for (int i=0; i<s.size(); ++i){
      if (!isalpha(s[i]) || !islower(s[i])){
	s.erase(i, 1);
	--i;
      }
    }
    for (int i=0; i<t.size(); ++i){
      if (!isalpha(t[i]) || !islower(t[i])){
	t.erase(i, 1);
	--i;
      }
    }
    string r = "";
    sort(s.begin(), s.end());
    sort(t.begin(), t.end());
    //cout << s << endl;
    //cout << t << endl;
    if (s.size() == 0 || t.size() == 0){
      cout << endl;
      continue;
    }

    if (s == t){
      cout << s << endl;
      continue;
    }
    for (int i=0, j=0; i < s.size() && j < t.size();){
      if (s[i] == t[j]){
	r += s[i];
	++i;
	++j;
      }else{
	while (s[i] < t[j]){
	  ++i;
	  if (i == s.size()) break;
	}
	while (t[j] < s[i]){
	  ++j;
	  if (j == t.size()) break;
	}
      }
    }
    cout << r << endl;
  }
  return 0;
}
