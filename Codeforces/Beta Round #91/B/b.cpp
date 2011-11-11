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

#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << x << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

int main(){
    int n, k;
    while (cin >> n >> k) {
        vector<string> numbers(n);
        for (int i = 0; i < n; ++i) cin >> numbers[i];
        
        vector<int> p(k);
        for (int i = 0; i < k; ++i) {
            p[i] = i;
        }
        
        int ans = 1 << 30;
        do {
            int biggest = -1, smallest = 1 << 30;

            for (int i = 0; i < n; ++i) {
                int x = 0;
                for (int j = 0; j < k; ++j) {
                    x = 10 * x + numbers[i][p[j]] - '0';
                }
                biggest = max(biggest, x);
                smallest = min(smallest, x);
            }
            
            ans = min(ans, biggest - smallest);
        } while (next_permutation(p.begin(), p.end()));
        cout << ans << endl;
    }
    return 0;
}