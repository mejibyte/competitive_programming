#include <iostream>
#include <map>
#include <cassert>

using namespace std;

typedef pair<int, int> par;

string line;
int total, pos;
bool error;
map<char, par> d;

void match(const string &s){
  //cout << "Matching: " << s << endl;
  for (int i=0, n = s.size(); i<n; ++i){
    assert(line[pos++] == s[i]);
  }
}

par E(){
  if (line[pos] == '('){
    match("(");
    par a = E();
    par b = E();
    //cout << "a es: (" << a.first << ", " << a.second << ")" << endl;
    //cout << "b es: (" << b.first << ", " << b.second << ")" << endl;
    if (a.second != b.first){
      error = true;
    }
    match(")");
    total += a.first * a.second * b.second;
    return par(a.first, b.second);
  }else if ('A' <= line[pos] && line[pos] <= 'Z'){
    char c = line[pos];
    match(string(1, c));
    return d[c];
  }
}

int main(){
  int n;

  cin >> n;
  while (n--){
    char c;
    int x, y;
    cin >> c >> x >> y;
    d[c] = par(x, y);
  }
  getline(cin, line);
  while (getline(cin, line) && line != ""){
    //cout << "line es: " << line << endl;
    total = pos = 0;
    error = false;
    E();
    if (error)
      cout << "error" << endl;
    else
      cout << total << endl;
  }
  return 0;
}
