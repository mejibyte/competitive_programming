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

const int MAXN = 1000005;
int v[MAXN];
int f, s, g, u, d;

bool can(int floor){
    if (floor <= 0 or floor > f) return false;
    return true;
}

int main(){
    cin >> f >> s >> g >> u >> d;
    
    for (int i = 1; i <= f; i++) v[i] = -1;
    queue <int> q;
    q.push(s);
    v[s] = 0;
    while (q.size() > 0){
        int curr = q.front();
        q.pop();
        if (curr == g) break;
        if (can(curr + u) and v[curr + u] == -1){
            q.push(curr + u);
            v[curr + u] = v[curr] + 1;
        }
        if (can(curr - d) and v[curr - d] == -1){
            q.push(curr - d);
            v[curr - d] = v[curr] + 1;
        }
    }
    
    if(v[g] == -1) puts("use the stairs");
    else cout << v[g] << endl;
    
    
    return 0;
}
