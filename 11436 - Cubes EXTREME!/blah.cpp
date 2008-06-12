#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

typedef unsigned long long ull;

int main(){
  ull n;
  while (cin >> n && n){
    vector<ull> d;
    for (ull i=1; i*i<=n; i++) {
      if (n%i == 0) {
	d.push_back(i);
	if (i*i<n) d.push_back(n/i);
      }
    } 
    sort(d.begin(), d.end());
    copy(d.begin(), d.end(), ostream_iterator<ull>(cout, " "));
    cout << endl;
  }
  return 0;
}
