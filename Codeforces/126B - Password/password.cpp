// Andrés Mejía
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <fstream>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <bitset>
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
using namespace std;

////////////// Prewritten code follows. Look down for solution. ////////////////
#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cerr << #x " is " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
////////////////////////// Solution starts below. //////////////////////////////


int main(){
    string text;
    cin >> text;

    // KMP.
    int n = text.size();
    vector<int> p(n);
    p[0] = 0;
    for (int i = 1; i < n; ++i) {
      p[i] = p[i - 1];
      while (p[i] > 0 && text[i] != text[p[i]]) {
        p[i] = p[p[i] - 1];
      }
      if (text[i] == text[p[i]]) {
        p[i]++;
      }
    }

    if (text.size() < 3) {
      cout << "Just a legend" << endl;
      return 0;
    }

    int max_middle = *max_element(p.begin() + 1, p.end() - 1);

    int answer = p[n - 1];
    while (answer > max_middle) {
      answer = p[answer - 1];
    }

    if (answer > 0) {
      cout << text.substr(0, answer) << endl;
    } else {
      cout << "Just a legend" << endl;
    }
    return 0;
}
