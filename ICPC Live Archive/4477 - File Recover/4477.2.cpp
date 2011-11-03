// Accepted.
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

template <class T> string toStr(const T &x){ stringstream s; s << x; return s.str(); }
template <class T> int toInt(const T &x){ stringstream s; s << x; int r; s >> r; return r; }

#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); x != (v).end(); ++x)
#define D(x) cout << #x " = " << (x) << endl

const int MAXN = 100005;

// Suffix array. O(n log^2 n) time, 16 bytes/char overhead.

// Input: text, N
// Output: sa[] is a sorted list of offsets to all non-empty suffixes,
// lcp[i] = length of longest common prefix of text+sa[i] and text+sa[i+1]
char text[MAXN]; long long key[MAXN]; int sa[MAXN], rank[MAXN], *lcp = (int *)key;
bool compare(int i, int j) { return key[i] < key[j]; }

void SuffixSort(int n) {
    for (int i = 0; i < n; ++i) { sa[i] = i; key[i] = text[i]; }
    sort(sa, sa + n, compare);
    for (int K = 1; ; K *= 2) {
        for (int i = 0; i < n; ++i) {
            rank[sa[i]] = ((i > 0 && key[sa[i-1]] == key[sa[i]]) ? rank[sa[i-1]] : i);
        }
        if (K >= n) break;
        for (int i = 0; i < n; ++i) {
            key[i] = rank[i] * (n + 1LL) + (i + K < n ? rank[i + K] + 1 : 0);
        }
        sort(sa, sa + n, compare);
    }

    for (int i = 0; i < n; ++i) assert(rank[sa[i]] == i);
    for (int i = 0, k = 0; i < n; ++i) {
        if (k > 0) k--;
        if (rank[i] == n - 1) { lcp[n - 1] = 0; k = 0; continue; }
        assert(rank[i] < n - 1);
        int j = sa[rank[i] + 1];
        while (text[i + k] == text[j + k]) k++;
        lcp[rank[i]] = k;
    }
    
    // lcp[0] = 0;
    // for (int i=0, h=0; i<n; ++i){
    //     if (rank[i] > 0){
    //         int j = sa[rank[i]-1];
    //         while (i + h < n && j + h < n && text[i+h] == text[j+h]) h++;
    //         lcp[rank[i]] = h;
    //         if (h > 0) h--;
    //     }
    // }
}

void solve(const string &s){
    int n = s.size();
    for (int i=0; i<n; ++i) text[i] = s[i];
    text[n] = '\0';

    SuffixSort(n);
    long long ans = 0;

    for (int i=0; i<n; ++i){
        if (lcp[i] > 0){
            ans += lcp[i] - min(lcp[i], lcp[i + 1]);
        }
    }
    cout << ans << endl;
}

int main(){
    string s;
    while (cin >> s && s[0] != '*'){
        solve(s);
    }
    return 0;
}
