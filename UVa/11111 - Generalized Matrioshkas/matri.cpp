#include <iostream>
#include <vector>
#include <stack>
#include <sstream>

using namespace std;

typedef long long ll;

//Verdadero si las sumas internas de [start, end] están correctas.
bool todo_bien(int start, int end, const vector<ll> &v, const vector<int> &jmp){

  int i = start+1;
  ll sum = 0;
  while (i < end){
    sum += -v[i];
    if (todo_bien(i, jmp[i], v, jmp) == false) return false;
    i = jmp[i]+1;
  }
  
  //cout << "Todo_bien entre " << start << " , " << end << ", sum = " << sum << " ans = " << (sum < v[end]) << endl;
  return (sum < v[end]);
}

int main(){
  string line;
  while (getline(cin, line)){
    vector<ll> v;
    stack<pair<ll, int> > stk;
    vector<int> jmp;
    
    int i = 0;
    stringstream sin(line);
    ll x;
    bool bad = false;
    while (sin >> x){
      v.push_back(x);
      jmp.push_back(-1);
      if (x < 0){
	stk.push(make_pair(x, i));
      }else{
	if (stk.size() == 0) bad = true;
	else{
	  ll y = stk.top().first;
	  int j = stk.top().second;
	  stk.pop();
	  if (x == -y){
	    jmp[i] = j;
	    jmp[j] = i;
	  }else bad = true;
	}
      }
      ++i;
    }
    if (stk.size()) bad = true;
    if (bad || !todo_bien(0, i-1, v, jmp)) cout << ":-( Try again." << endl;
    else cout << ":-) Matrioshka!" << endl;
  }
  return 0;
}
