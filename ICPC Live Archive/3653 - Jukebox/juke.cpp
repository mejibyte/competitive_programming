// Andrés Mejía
// Time Limit and Wrong Answer
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

map<string, int> artist_id;
int total_artists;
int total_songs;
string artists[6];
vector<int> songs_by[6];
int assign[6];
string titles[30];
int artist_of[30];

const int MAXN = 1000;
int belong[MAXN];
int length[MAXN];

namespace SuffixArray {
    int t, rank[MAXN], sa[MAXN], lcp[MAXN];

    bool compare(int i, int j){
        return rank[i + t] < rank[j + t];
    }
    
    void build(const string &s){
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
                    k = rank[*start + t];
                    if (k != first and (i > first or k >= j))
                        first = k, num = start - sa;
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

int next[MAXN], prev[MAXN], min_next[MAXN], min_prev[MAXN];

int candidate[35];

const int oo = 1e6;

int solve() {
    string text = "";
    
    for (int i = 0; i < total_songs; ++i){
        int my_artist = artist_of[i];
        if (assign[my_artist] == i) {
            text += artists[my_artist];
        } else {
            text += titles[i];
        }
        text += char(i + 2);
    }
    text += char(1);
    
    // for(int i = 0; i < text.size(); ++i) {
    //     if (text[i] < '_') {
    //         cout << " $" << int(text[i] - 2) << " ";
    //     } else {
    //         cout << text[i];
    //     }
    // }
    // cout << endl;
    
    for (int i = text.size() - 1; i >= 0; --i) {
        if (text[i] < '_') {
            length[i] = 0;
            belong[i] = int(text[i]) - 2;
        } else {
            length[i] = length[i + 1] + 1;
            belong[i] = belong[i + 1];
        }
        assert(-1 <= belong[i] and belong[i] < total_songs);
    }
    
    SuffixArray::build(text);
    assert(SuffixArray::sa[0] == text.size() - 1);
    
    int n = text.size();
    for (int i = 0; i < total_songs; ++i) candidate[i] = oo;
    
    next[n - 1] = n;
    min_next[n - 1] = 0;
    for (int i = n - 2; i >= 0; --i){
        if (belong[SuffixArray::sa[i]] == belong[SuffixArray::sa[i+1]]) {
            next[i] = next[i + 1];
            min_next[i] = min(SuffixArray::lcp[i + 1], min_next[i + 1]);
        } else {
            next[i] = i + 1;
            min_next[i] = SuffixArray::lcp[i + 1];
        }
    }
    
    prev[0] = -1;
    min_prev[0] = 0;
    for (int i = 1; i < n; ++i) {
        if (belong[SuffixArray::sa[i]] == belong[SuffixArray::sa[i-1]]) {
             prev[i] = prev[i - 1];
             min_prev[i] = min(SuffixArray::lcp[i], min_prev[i - 1]);
         } else {
             prev[i] = i - 1;
             min_prev[i] = SuffixArray::lcp[i];
         }        
    }
    
    // for (int i = 0; i < n; ++i) {
    //     int from = SuffixArray::sa[i];
    //     int len = length[from];
    //     
    //     printf("lcp = %d, %30s, min = %d pointing to %d\n", SuffixArray::lcp[i], text.substr(from, len).c_str(), min_prev[i], prev[i]);
    // }
    
    for (int i = 0; i < n; ++i) {
        int need = max(min_next[i], min_prev[i]) + 1;
        int who = belong[SuffixArray::sa[i]];
        if (who == -1) continue;
        if (need <= length[SuffixArray::sa[i]]) {
            candidate[who] = min(candidate[who], need);
        }
    }
    
    int ans = 0;
    for (int i = 0; i < total_songs; ++i) {
        ans += candidate[i];
        ans = min(ans, oo);
    }
    return ans;
}


int total_cases;

int generate(int i, int which = 0) {
    if (i == total_artists) {
        // solve here
        //cout << total_cases++ << endl;
        return solve();
    } else {
        int ans = oo;
        for (int k = -1; k < (int)songs_by[i].size(); ++k) {
            if (k == -1) {
                assign[i] = k;
            } else {
                assign[i] = songs_by[i][k];
            }
            ans = min(ans, generate(i + 1));
        }
        return ans;
    }
}

int main(){
    while (cin >> total_songs) {
        if (total_songs == 0) break;
        for (int i = 0; i < 6; ++i) songs_by[i].clear();
        artist_id.clear();
        total_artists = 0;
        total_cases = 0;
        
        for (int i = 0; i < total_songs; ++i) {
            string artist;
            cin >> titles[i] >> artist;
            int id = artist_id.count(artist) ? artist_id[artist] : artist_id[artist] = total_artists++;
            artists[id] = artist;
            songs_by[id].push_back(i);
            artist_of[i] = id;
        }
        assert(total_artists <= 6);
        cout << generate(0) << endl;
    }
    return 0;
}