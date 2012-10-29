// Andrés Mejía
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

////////////// Prewritten code follows. Look down for solution. ////////////////
#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
////////////////////////// Solution starts below. //////////////////////////////

string phone[] = {"*", "*", "ABC" "DEF" "GHI", "JKL", "MNO", "PQRS", "TUV", "WXYZ"};

int main(){
    int runs; cin >> runs;
    while (runs--) {
        string name; cin >> name;
        vector<int> number;
        for (int i = 0; i < name.size(); ++i) {
            char c = toupper(name[i]);
            assert('A' <= c and c <= 'Z');
            for (int i = 2; i < 10; ++i) {
                if (phone[i].find(c) != string::npos) {
                    number.push_back(i);
                    break;
                }
            }
        }
        vector<int> number2 = number;
        assert(number.size() == name.size());
        reverse(number2.begin(), number2.end());
        cout << (number == number2 ? "YES" : "NO") << endl;
    }
    
    return 0;
}