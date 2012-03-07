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

////////////// Prewritten code follows. Look down for solution. ////////////////
#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
////////////////////////// Solution starts below. //////////////////////////////

string seq;
int nextToken;

vector< int > merge(const vector< int > &left, const vector< int > &right) {
    vector< int > ans;
    int l = 0, r = 0;
    while (l < left.size() and r < right.size()) {
        if (seq[nextToken++] == '1') { // take left
            ans.push_back( left[l++] );
        } else { // take right
            ans.push_back( right[r++] );
        }
    }
    while (l < left.size()) ans.push_back( left[l++] );
    while (r < right.size()) ans.push_back( right[r++] );
    return ans;
}

vector< int > generate(int smallest, int i, int j) {
    int n = j - i + 1;
    if (n == 1) {
        return vector< int >(1, smallest);
    }
    int mid = n / 2;
    
    vector< int > left = generate(smallest, 0, mid - 1);
    vector< int > right = generate(smallest + left.size(), mid, n - 1);
    
    return merge(left, right);
}

void solve() {
    int n; cin >> n >> seq;
    nextToken = 0;
    vector< int > permutation = generate(1, 0, n - 1);
    assert( permutation.size() == n );
    vector< int > reverse_permutation(n);
    for (int i = 0; i < n; ++i) {
        reverse_permutation[ permutation[i] - 1 ] = i + 1;
    }
    // foreach(p, reverse_permutation) printf("%d ", *p); puts("");
    int hash = 1;
    for (int i = 0; i < n; ++i) {
        hash = (31 * hash + reverse_permutation[i]) % 1000003;
    }
    printf("%d\n", hash);
}

int main(){
    int runs; cin >> runs;
    for (int i = 1; i <= runs; ++i){
        printf("Case #%d: ", i);
        solve();
    }
    return 0;
}