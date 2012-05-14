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
#define For (i, a, b) for (int i = (a); i < (b); i++)

#define MAXN 1000

typedef long long ll;

ll w[MAXN+5];

bool greater_first (const int &a, const int &b) {
    return w[a] > w[b];   
}
bool smaller_first (const int &a, const int &b) {
    return w[a] < w[b];   
}

int main (){
    int run = 1;
    int n;
    while(cin>>n) {
        if (n == 0) break;
        
        string from,to;
        cin>>from>>to;
        for (int i = 0; i < n; ++i) {
            cin>>w[i];   
        }
        
        
        printf("Case %d: ",run++);
        cout<<res<<endl;
    }

    return 0;
}
