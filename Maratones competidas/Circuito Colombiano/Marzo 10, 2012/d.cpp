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
#include <map>
#include <set>

#define For (i, a, b) for (int i = (a); i < (b); i++)
#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); x != (v).end(); x++)
#define D(x) cout << #x " = " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS){
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

const double increment = 0.0000152587890625;

string codes = "PQWERTYUIOJ#SZK*?F@D!HNM&LXGABCV";

int main() {
    
    int casos; cin >> casos;
    while (casos--) {
        int id; cin >> id;
        
        char a; int b; char c;
        cin >> a >> b >> c;
        
        vector<int> bits;
        if (c == 'D') bits.push_back(1); else bits.push_back(0);
        
        for (int i = 0; i < 11; ++i)  bits.push_back( !!(b & (1 << i)) );
        
        for (int i = 0; i < codes.size(); ++i) if (a == codes[i]) {
            for (int j = 0; j < 5; ++j) bits.push_back(  !!(i & (1 << j))  );
        }
        
        reverse(bits.begin(), bits.end());
        
        double ans = 0;
        for (int i = 1; i < bits.size(); ++i) {
            if (bits[i] == 1) {
                ans += 1.0 / pow(2.0, i);
            }
        }
        if (bits[0] == 1) {
            ans = -(1.0 - ans);
        }
        
        char buf[200];
        sprintf(buf, "%.20lf", ans);
        string s(buf);
        while (s[s.size() - 1] == '0') s.resize(s.size() - 1);
        if (s[s.size() - 1] == '.') s = s + "0";
        cout << id << " " << s << endl;
        
    }
    
    return 0;
}
