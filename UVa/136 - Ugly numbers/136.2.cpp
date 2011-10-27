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

int main(){
    vector<long long> ugly;
    ugly.push_back(1);
    
    priority_queue<long long, vector<long long>, greater<long long> > q;
    q.push(1);
    
    while (ugly.size() < 1500) {
        long long v = q.top();
        q.pop();
        if (ugly.back() != v) {
            ugly.push_back(v);
        }
        if (v % 3 != 0 and v % 5 != 0) {
            q.push(v * 2);
        }
        
        if (v % 5 != 0) {
            q.push(v * 3);
        }
        q.push(v * 5);
    }
    // for (int i = 0; i < 100; ++i) {
    //     printf("ugly[%d] = %lld\n", i, ugly[i]);
    // }
    printf("The 1500'th ugly number is %lld.\n", ugly[1499]);
    
    return 0;
}