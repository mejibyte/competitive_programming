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
    int x1, times, position;
    while (cin >> x1 >> times >> position) {
        if (x1 == 0 and times == 0 and position == 0) break;
        vector< int > v;
        while (x1 > 0) v.push_back(x1 % 10), x1 /= 10;
        reverse(v.begin(), v.end());
        
        //printf("V is "); For(i, 0, v.size()) printf("%d ", v[i]); puts("");
        
        for (int t = 0; t < times - 1; ++t) {
            vector< int > w;

            for (int i = 0; i < v.size(); ) {
                int j = i;
                while (j < v.size() and v[i] == v[j]) j++;
                int size = j - i;
                //printf("%d appears %d times from [%d,%d)\n", v[i], size, i, j);
                int n = w.size();
                while (size > 0) w.push_back(size % 10), size /= 10;
                reverse(w.begin() + n, w.end());
                w.push_back(v[i]);
                
                if (w.size() > 3000) break;
                i = j;
            }
            
            v = w;
            //printf("V is "); For(i, 0, v.size()) printf("%d ", v[i]); puts("");
        }
        cout << v[position - 1] << endl;
    }
    return 0;
}