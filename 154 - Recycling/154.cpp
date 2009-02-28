/*
  Problem: 154 - Recycling
  Andrés Mejía-Posada (andmej@gmail.com)
 */
using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <fstream>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <deque>
#include <stack>
#include <list>
#include <map>
#include <set>

#define D(x) cout << #x " is " << x << endl

vector<int> score;
vector<string> lines;

int diff(string a, string b){
  map<char, char> ma, mb;
  for (int i=0; i<20; i += 4){
    ma[a[i]] = a[i+2];
    mb[b[i]] = b[i+2];
  }
  const string letters = "bogry";
  int ans = 0;
  for (int i=0; i<letters.size(); ++i){
    ans += (ma[letters[i]] != mb[letters[i]]);
  }
  return ans;
}

int main(){
  string s;
  while (getline(cin, s) && s != "#"){
    lines.clear();
    lines.push_back(s);
    while (getline(cin, s) && s[0] != 'e'){
      lines.push_back(s);
    }
    int n = lines.size();
    score.resize(n);
    for (int i=0; i<n; ++i){
      score[i] = 0;
      for (int j=0; j<n; ++j){
        score[i] += diff(lines[i], lines[j]);
      }
    }
    printf("%d\n", min_element(score.begin(), score.end()) - score.begin() + 1);
  }
  return 0;
}
