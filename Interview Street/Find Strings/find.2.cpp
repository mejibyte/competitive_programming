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

const int MAXN = 2005 * 55;

namespace SuffixArray {
    int t, rank[MAXN], sa[MAXN], lcp[MAXN];

    bool compare(int i, int j){
        return rank[i + t] < rank[j + t];
    }
    
    void compute(const string &s){
        int n = s.size();
        
        int bc[256];
        for (int i = 0; i < 256; ++i) bc[i] = 0;
        for (int i = 0; i < n; ++i) ++bc[s[i]];
        for (int i = 1; i < 256; ++i) bc[i] += bc[i-1];
        for (int i = 0; i < n; ++i) sa[--bc[s[i]]] = i;
        for (int i = 0; i < n; ++i) rank[i] = bc[s[i]];
        for (t = 1; t < n; t <<= 1){
            for (int i = 0, j = 1; j < n; i = j++){
                while (j < n && rank[sa[j]] == rank[sa[i]]) j++;
                if (j - i == 1) continue;
                int *start = sa + i, *end = sa + j;
                sort(start, end, compare);
                int first = rank[*start + t], num = i, k;
                for(; start < end; rank[*start++] = num){
                    if ((k = rank[*start + t]) != first and (i > first or k >= j)) {
                        first = k, num = start - sa;
                    }
                }
            }
        }

        // Remove this part if you don't need the LCP
        int size = 0, i, j;
        for(i = 0; i < n; i++) if (rank[i] > 0) {
            j = sa[rank[i] - 1];
            while(s[i + size] == s[j + size]) ++size;
            lcp[rank[i]] = size;
            if (size > 0) --size;
        }
        lcp[0] = 0;
    }
};


int main(){
    ios::sync_with_stdio(false);
    
    int n;
    cin >> n;
    
    string s;
    for (int i = 0; i < n; ++i) {
        string t; cin >> t;
        s += t + char(i + 1);
    }
    SuffixArray::compute(s);
    
    // s = "abacabadaba";
    // SuffixArray::compute(s);
    // for (int i = 0; i < s.size(); ++i) {
    //     printf("sa[%d] = %d (%s)\n", i, SuffixArray::sa[i], s.substr(SuffixArray::sa[i]).c_str() );
    // }
    // 
    // for (int i = 0; i < s.size(); ++i) {
    //     printf("ranks[%d] = %d\n", i, SuffixArray::rank[i]);
    // }
    // 
    // for (int i = 0; i < s.size(); ++i) {
    //     printf("lcp[%d] = %d\n", i, SuffixArray::lcp[i]);
    // }
    // return 0;
    
    n = s.size();
    
    // Precomputar el arreglo L
    vector<int> L(n);
    for (int i = n - 1, len = 0; i >= 0; --i) {
        len++;
        if (s[i] < 'a') len = 0; // encontré un $
        L[SuffixArray::rank[i]] = len;
    }
    
    
    int queries; cin >> queries;
    while (queries--) {
        int k; cin >> k;
        
        bool found = false;
        for (int i = 0; i < n; ++i) {
            int r = L[i] - SuffixArray::lcp[i];
            if (r >= k) {
                cout << s.substr(SuffixArray::sa[i], SuffixArray::lcp[i] + k) << endl;
                found = true;
                break;
            } else {
                k -= r;
            }
        }
        if (!found) cout << "INVALID" << endl;
    }
    
    
    return 0;
}