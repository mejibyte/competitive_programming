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

int r(int max = 10) {
    return rand() % (max + 1);
}

int main(){
    int runs = 100;
    srand(time(NULL));
    cout << runs << endl;
    while (runs--) {
        cout << r() << " " << r() << " " << r() << " " << r() << endl;
        int chips = rand() % 3;
        cout << chips << endl;
        while (chips--) {
            cout << r() << " " << r() << " " << r() << " " << r() << endl;            
        }
    }
    return 0;
}