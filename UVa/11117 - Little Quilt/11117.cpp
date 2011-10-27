/*
  Accepted
 */
#include <iostream>
#include <vector>
#include <cassert>


using namespace std;

typedef vector<vector<char> > matrix;


string e;
int pos;
bool error;
matrix a, b, empty;


void match(const string &s){
  int n = s.size();
  for (int i=0; i<n; ++i){
    assert(e[pos++] == s[i]);
  }
}

void print(const matrix &a){
  for (int i=0; i<a.size(); ++i){
    for (int j=0; j<a[i].size(); ++j){
      cout << a[i][j];
    }
    cout << endl;
  }
  //cout << endl;
}


matrix turn(const matrix &t){
  matrix r;
  for (int j = 0; j < t[0].size(); ++j){
    r.push_back(vector<char>());
    for (int i = t.size()-1; i >= 0; --i){
      r.back().push_back(t[i][j]);
    }
  }

  for (int i=0; i<r.size(); ++i){
    for (int j = 0; j<r[i].size(); ++j){
      if (r[i][j] == '/') r[i][j] = '\\';
      else if (r[i][j] == '\\') r[i][j] = '/';
      else if (r[i][j] == '-') r[i][j] = '|';
      else if (r[i][j] == '|') r[i][j] = '-';
    }
  }
  return r;
}

matrix sew(matrix x, const matrix &y){
  if (x.size() != y.size()){
    ::error = true;
    return empty;
  }
  for (int i=0; i<y.size(); ++i){
    for (int j=0; j<y[i].size(); ++j){
      x[i].push_back(y[i][j]);
    }
  }
  return x;
}


matrix Q(){
  if (e[pos] == 'A'){
    match("A");
    return a;
  }else if (e[pos] == 'B'){
    match("B");
    return b;
  }else if (e[pos] == 't'){
    match("turn(");
    matrix t = Q();
    if (::error) return empty;
    match(")");
    return turn(t);
  }else if (e[pos] == 's'){
    match("sew(");
    matrix x = Q();
    if (::error) return empty;
    match(",");
    matrix y = Q();
    if (::error) return empty;
    match(")");
    matrix s = sew(x, y);
    return s;
  }
}

void initialize(){
  a = vector<vector<char> >(2, vector<char>(2, '/'));
  a[1][1] = '+';

  //print(a);

  b = vector<vector<char> >(2, vector<char>(2, '-'));

  //print(b);

  empty = vector<vector<char> >();
}


int main(){
  int quiltNo = 1;
  initialize();
  while (!cin.eof()){
    char c;
    e = "";
    pos = 0;
    ::error = false;
    while (cin >> c && c != ';'){
      e += c;
    }
    if (e == "") break;
    matrix q = Q();

    cout << "Quilt " << quiltNo++ << ":" << endl;
    //cout << e << endl;
    if (::error){
      cout << "error" << endl;
    }else{
      print(q);
    }
  }
  return 0;
}

