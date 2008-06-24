#include <map>
#include <iostream>
#include <string>

using namespace std;

int main(){
  int words, jobs;
  map<string, unsigned long long> dict;
  string s;
  unsigned long long d;
  cin >> words >> jobs;
  for (int i=0; i<words; ++i){
    cin >> s >> d;
    dict[s] = d;
  }

  while (jobs--){
    unsigned long long total = 0;
    while (cin >> s && s != "."){
      map<string, unsigned long long>::iterator i = dict.find(s);
      if (i != dict.end()){
        total += i->second;
      }
    }
    cout << total << endl;
  }
  return 0;
}
