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


int sum(int to) {
    return to * (to + 1) / 2;
}

const int MAXN = 13;

int ppl[MAXN], n;

int hash(int r, int c) {
    int ans = 13 * r + c;
    for (int i = 0; i < n; ++i) {
        ans = 13 * ans + ppl[i];
        ans %= (1 << 20);
    }
    return ans;
}

int memo[1 << 20];

const int oo = 1000;
int f(int r, int c, int total) {
    //printf("r = %d, c = %d\n", r, c);
    
    int seats = sum(12) - sum(r - 1) - c + 1;
    if (total > seats) return oo;
    
    if (total == 0) return r;
    
    if (r > 12) return oo;

    if (c > r) { return f(r + 1, 1, total); }

    int key = hash(r, c); if (memo[key] > 0) return memo[key];

    int ans = f(r, c + 1, total);
    int remain = r - c + 1;
    int tmp;
    for (int i = 0; i < n; ++i) {
        if (ppl[i] == 0) continue;
        int size = i + 1;
        if (size > remain) break;
        if (size < remain) { // agregar huequito despues del grupo
            ppl[i]--;
            tmp = f(r, c + size + 1, total - size);
            if (tmp < ans) ans = tmp;
            ppl[i]++;
        } else if (size == remain) { // ponerlo y bajar de fila (sin hueco)
            ppl[i]--;
            tmp = f(r, c + size, total - size);
            if (tmp < ans) ans = tmp;
            ppl[i]++;
        }
    }
    return memo[key] = ans;
    return ans;
}

int main(){
    cin >> n;
    int num_ppl = 0;
    for (int i = 0; i < n; i++){
        cin >> ppl[i];
        num_ppl += ppl[i] * (i + 1);
    }
    if (num_ppl > sum(12)) { puts("impossible"); return 0; }
    
    int ans = f(1, 1, num_ppl);
    if (ans < 13) printf("%d\n", ans);
    else puts("impossible");
    

    
    return 0;
}
