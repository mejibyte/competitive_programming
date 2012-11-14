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

#include <iomanip>

int main(){
    double best = -1;
    string which;
    string s;
    cin >> s;
    while (!cin.eof()) {
        string name = s.substr(1);
        string dna = "";
        while (cin >> s and s[0] != '>') dna += s;
        
        int count = 0;
        for (int i = 0; i < dna.size(); ++i) count += dna[i] == 'C' or dna[i] == 'G';
        
        if (1.0 * count / dna.size() > best) {
            best = 1.0 * count / dna.size();
            which = name;
        }
    }
    cout << which << endl;
    cout << fixed << setprecision(10) << 100.0 * best << "%" << endl;
    return 0;
}