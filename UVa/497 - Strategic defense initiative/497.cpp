#include <iostream>
#include <sstream>
#include <vector>
#include <cassert>
#include <iterator>

using namespace std;

void print(vector<int> &a, vector<int> &p, const int &i){
  if (p[i] != -1){
    print(a, p, p[i]);
  }
  cout << a[i] << endl;
}

int main(){
  int casos;
  cin >> casos; while (getchar() != '\n');
  string s;
  getline(cin, s);
  bool first = true;
  while (casos--){
    if (!first) cout << endl;
    first = false;
    vector<int> a;
    while (getline(cin, s) && s != ""){
      stringstream ss(s);
      int x;
      ss >> x;
      a.push_back(x);      
    }
    assert(a.size() > 0);
    vector<int> p(a.size());
    vector<int> dp(a.size());
    for (int i=0; i<a.size(); ++i){
      p[i] = -1;
      dp[i] = 1;
      //      cout << "i es: " << i << endl;
      for (int j=0; j<i; ++j){
	//cout << "  j es: " << j << endl;
	if (a[i] > a[j] && dp[j] + 1 > dp[i]){
	  dp[i] = dp[j] + 1;
	  p[i] = j;
	}
      }
    }
    
    //    cout << "a es: "; copy(a.begin(), a.end(), ostream_iterator<int>(cout, " "));
    //    cout << endl;

    //    cout << "dp es: "; copy(dp.begin(), dp.end(), ostream_iterator<int>(cout, " "));
    //    cout << endl;

    int best = dp[0];
    int indexMax = 0;
    for (int i=0; i<a.size(); ++i){
      if (dp[i] > best){
	best = dp[i];
	indexMax = i;
      }
    }
    cout << "Max hits: " << best << endl;
    print(a, p, indexMax);
  }
  return 0;
}
