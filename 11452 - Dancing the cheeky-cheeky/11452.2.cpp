/*
  Accepted
 */
#include <iostream>

using namespace std;

int main(){
  int C;
  string s;
  cin >> C;
  getline(cin, s);
  while (C--){
    getline(cin, s);
    
    int n = s.size();
    int i, j;
    for (i=1; i<=n; ++i){
      string first(s.substr(0, i)), second(s.substr(i, i));
      if (first == second  &&  n - 2*i < i){
	//cout << "Solution found using first " << i << " chars." << endl;
	break;
      }
    }
    
    j = n - 2*i;
    for (int k=0; k<8; ++k){
      cout << s[j];
      j = (j+1)%(2*i);
    }
    cout << "..." << endl;
  }
  return 0;
}
