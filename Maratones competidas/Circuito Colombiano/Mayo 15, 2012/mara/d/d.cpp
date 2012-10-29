using namespace std;
#include <iostream>
#include <algorithm>
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
#include <map>
#include <set>
#include <stack>

#define D(x) cout << #x " = " << (x) << endl
#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); x != (v).end(); x++)
#define For(i, a, b) for (int i = (a); i < (b); i++)

vector<long long> v;

int main (){
    
    for (long long i = 1; i * (i + 1) / 2 <= 1000000000; ++i) {
        long long sum = i * (i + 1) / 2;
        
        long long root = floor(sqrt(sum + 1) + 1e-9);
        if (root * root == sum + 1) {
            v.push_back(sum+1);  
        }
             
    }
    
    int a, b;
    int run = 1;
    while (cin >> a >> b) {
        if (a == 0 and b == 0) break;
        
        printf("Case %d: ", run++);
        int ans = 0;
        for (int i = 0; i < v.size(); ++i) {
            if (a < v[i] and v[i] < b) ans++;
            if (v[i] > b) break;
        }
        printf("%d\n", ans);
    }
    return 0;    
}
