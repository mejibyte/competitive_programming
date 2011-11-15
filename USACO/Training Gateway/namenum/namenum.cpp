/*
  LANG: C++
  PROB: namenum
*/
using namespace std;
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

////////////// Prewritten code follows. Look down for solution. ////////////////
#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cerr << #x " is " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
////////////////////////// Solution starts below. //////////////////////////////


int number[26] = { 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, -1, 7, 7, 8, 8, 8, 9, 9, 9, -1 };

int main(){
    freopen("namenum.in", "r", stdin);
    freopen("namenum.out", "w", stdout);
    
    long long cow; cin >> cow;
    
    fstream dict("dict.txt");
    assert(!dict.fail());
    string word;
    int cnt = 0;
    while (dict >> word) {
        if (word.find_first_of("QZ") != string::npos) continue;

        long long x = 0;
        for (int i = 0; i < word.size(); ++i) {
            x = x * 10 + number[ word[i] - 'A' ];
        }

        if (x == cow) {
            cout << word << endl;
            cnt++;
        }
    }
    if (cnt == 0) {
        cout << "NONE" << endl;
    }
    
    return 0;
}