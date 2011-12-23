// Andrés Mejía
// Time limit. Shit!
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

const int MAXN = 2000005;
char buffer[2 * MAXN];
int border[2 * MAXN];
unsigned int hash[MAXN];

vector< string > words;
map< unsigned int, int > repeats[2];


long long calculate(int W, int index) {
    for (int i = 0; i < W; ++i) {
        unsigned int hash = 5381;
        for (int j = words[i].size() - 1; j >= 0; --j) {
            hash = hash * 33 + words[i][j];
        }
        repeats[index][hash]++;
        //printf("%u++ for a total of %d times\n", hash, repeats[hash]);
    }

    long long ans = 0;

    for (int k = 0; k < W; ++k) {
        const string &s = words[k];
        int n = s.size();
        for (int i = 0; i < n; ++i) {
            buffer[i] = s[n - 1 - i];
            buffer[n + 1 + i] = s[i];
        }
        buffer[n] = '$';
        buffer[2 * n + 1] = '\0';

        // Buffer == Reverse(s) + $ + s
        border[0] = 0;
        for (int i = 1; i < 2 * n + 1; ++i) {
            int size = border[i - 1];
            while (size > 0 and buffer[i] != buffer[size]) size = border[size - 1];
            if (buffer[i] == buffer[size]) size++;
            border[i] = size;
        }
        ::hash[0] = 5381 * 33 + s[0];
        for (int i = 1; i < n; ++i) {
            ::hash[i] = ::hash[i - 1] * 33 + s[i];
        }
        // printf("Buffer is %s\n", buffer);
        //       for (int i = 0; i < 2 * n + 1; ++i) {
        //           printf("%d ", border[i]);
        //       }
        //       puts("");
      
        int len = border[2 * n];
        while (len > 0) {
            unsigned int prefix = (n - 1 - len == -1) ? 5381 : ::hash[n - 1 - len];
            ans += repeats[index][prefix];
            len = border[len - 1];
        }
    }
    return ans;
}

int main(){
    int W;
    scanf("%d", &W);
    words.resize(W);
    for (int i = 0; i < W; ++i) {
        int len; scanf("%d %s ", &len, buffer);
        words[i] = string(buffer);
    }
    
    long long ans = calculate(W, 0); 
    for (int i = 0; i < W; ++i) { // Same length
        unsigned int hash = 5381;
        for (int j = 0; j < words[i].size(); ++j) {
            hash = hash * 33 + words[i][j];
        }
        ans += repeats[0][hash];
        
        reverse(words[i].begin(), words[i].end());
    }
    ans += calculate(W, 1);
    
    printf("%lld\n", ans);

    return 0;
}