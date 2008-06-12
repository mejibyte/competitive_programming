#include <vector>
#include <map>
#include <iostream>
#include <string>

using namespace std;

map<char, char> solution;

const string key = "the quick brown fox jumps over the lazy dog";

bool solve(const string &s){
  map<char, char> m, n;
  if (s.length() != key.length()){
    return false;
  }
  for (int i=0; i<s.length(); ++i){
    if (s[i] == ' '){
      if (key[i] != ' ') return false;
    }else{
      //mapear s[i] a key[i]
      if (m.count(s[i]) > 0){ //ya estaba mapeada
	if (m[s[i]] != key[i]){
	  return false;
	}
      }else{
	if (n.count(key[i]) > 0){
	  if (n[key[i]] != s[i]) return false;
	}
	m[s[i]] = key[i];
	n[key[i]] = s[i];
      }
    }
  }
  solution = m;
  return true;
}

int main(){
  int cases;
  cin >> cases;
  getchar();
  getchar();
  for (int k = 0; k < cases; ++k){
    if (k>0) cout << endl;

    vector<string> lines;
    string l;
    bool solved = false;
    //    cout << "Caso " << cases << endl;
    while (getline(cin, l) && l != ""){
      lines.push_back(l);
      //cout << l << " - Solution: " << (solve(l)?"True":"False") << endl;
      if (!solved) solved = solve(l);
    }

    if (solved){
      for (int i=0; i<lines.size(); ++i){
	string s = lines[i];
	for (int j=0; j<s.size(); ++j){
	  if (s[j] == ' ') cout << " ";
	  else{
	    cout << solution[s[j]];
	  }
	}
	cout << endl;
      }
    }else{
      cout << "No solution.\n";
    }
    
  }
  return 0;
}
