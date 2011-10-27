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
    string line;
    while (getline(cin, line)) {
        int cnt = 0;
        int n = line.size();
        for (int i = 0; i < n; ++i) {
            if (isalpha(line[i])) {
                cnt++;
                while (i < n and isalpha(line[i])) i++;
                i--;
            }
        }
        printf("%d\n", cnt);
    }
    return 0;
}