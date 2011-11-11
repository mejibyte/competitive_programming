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

const long long oo = 1LL<<62;

struct subject {
    long long a, b;
    int c, idx;
    subject(){}
    bool operator < (const subject &t) const {
        if (c != t.c) return c < t.c;
        if (a != t.a) return a < t.a;
        return b < t.b;
    }
};

int N;
long long K;
vector< subject > subjects;

map< pair<int, pair<int, long long > >, long long > memo;

map< pair<int, pair<int, long long > >, pair<int, long long> > choice;

long long f(int k, int last, long long exercises) {
    if (k == N) {
        //printf("f(k=%d, last=%d, exercises=%lld) = %lld.\n", k, last, exercises, 0LL);
        return 0LL;
    }
    
    pair<int, pair<int, long long > > key = make_pair(k,  make_pair(last, exercises));
    if (memo.count(key)) return memo[key];
    
    
    long long ans = -oo;
    long long choose_exercises = -1;
    int choose_next = -1;
    
    for (int j = last + 1; j < subjects.size(); ++j) {
        const subject &cur = subjects[j];
        if (last >= 0) {
            assert(cur.c >= subjects[last].c);
            if (cur.c == subjects[last].c) continue; // must be strictly increasing
            
            long long new_exercises[2];
            
            new_exercises[0] = exercises + K;
            new_exercises[1] = exercises * K;
            
            for (int p = 0; p < 2; ++p) {
                if (cur.a <= new_exercises[p] and new_exercises[p] <= cur.b) {
                    long long option = f(k + 1, j, new_exercises[p]) + new_exercises[p];
                    if (option > ans) {
                        ans = option;
                        choose_exercises = new_exercises[p];
                        choose_next = j;
                    }
                }
            }
            
        } else { // can choose whatever number of exercises I want
            assert(k == 0);
            for (long long e = cur.a; e <= cur.b; ++e) {
                long long option = f(k + 1,  j,  e) + e;
                if (option > ans) {
                    ans = option;
                    choose_exercises = e;
                    choose_next = j;
                }
            }
        }
    }
 
    //if (ans < oo) printf("f(k=%d, last=%d, exercises=%lld) = %lld. Next is %d with %lld extra exercises\n", k, last, exercises, ans, choose_next, choose_exercises);
    memo[key] = ans;
    choice[key] = make_pair(choose_next, choose_exercises);
    return ans;
}


int main(){
    int m;
    while (cin >> N >> m >> K) {
        subjects.resize(m);
        For(i, 0, m) {
            cin >> subjects[i].a >> subjects[i].b >> subjects[i].c;
            subjects[i].idx = i;
        }
        sort(subjects.begin(), subjects.end());
        // For(i, 0, m) {
        //     printf("Subject %d = (a=%lld, b=%lld, c=%d)\n", i, subjects[i].a, subjects[i].b, subjects[i].c);
        // }
        memo.clear();
        long long ans = f(0, -1, 0);
        if (ans < 0) {
            cout << "NO" << endl;
        } else {
            cout << "YES" << endl;
            
            int k = 0, last = -1; long long e = 0;
            for (int i = 0; i < N; ++i) {
                pair<int, pair<int, long long > > key = make_pair(k,  make_pair(last, e));
                pair< int, long long > c = choice[key];
                cout << subjects[c.first].idx + 1 << " " << c.second << endl;
                
                k++;
                last = c.first;
                e = c.second;
            }
        }
    }
    return 0;
}