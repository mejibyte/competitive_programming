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

const long double EPS = 1e-17L;
int cmp(double x, double y = 0, double tol = EPS){
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

string codes = "PQWERTYUIOJ#SZK*?F@D!HNM&LXGABCV";

long double get(char a, int b, char c) {
        vector<int> bits;
        if (c == 'D') bits.push_back(1); else bits.push_back(0);
        
        for (int i = 0; i < 11; ++i)  bits.push_back( !!(b & (1 << i)) );
        
        for (int i = 0; i < codes.size(); ++i) if (a == codes[i]) {
            for (int j = 0; j < 5; ++j) bits.push_back(  !!(i & (1 << j))  );
        }
        
        reverse(bits.begin(), bits.end());
        
        long double ans = 0;
        for (int i = 1; i < bits.size(); ++i) {
            if (bits[i] == 1) {
                ans += 1.0 / pow(2.0, i);
            }
        }
        if (bits[0] == 1) {
            ans = -(1.0 - ans);
        } 
        return ans;
}


int main() {
 map< long double, string > nums;
    for (int i = 0; i < codes.size(); ++i) {
        for (int b = 0; b < (1 << 11); ++b) {
            
            char buf[100]; sprintf(buf, "%d", b);
            
            nums[ get(codes[i], b, 'F') ] = codes.substr(i, 1) + " " + string(buf) + " F";
            nums[ get(codes[i], b, 'D') ] = codes.substr(i, 1) + " " + string(buf) + " D";                

        }
    }
    
    int casos; cin >> casos;
    while (casos--) {
        int id; long double v;
        cin >> id >> v;
        printf("%d ", id);
        
        if (v < -1.0 or v >= 1.0) {
            printf("INVALID VALUE\n");
            continue;
        }

        map< long double, string >::iterator i = nums.lower_bound( v );    
        if (v >= 0 and cmp(i->first, v) != 0) i--;
        cout << i->second << endl;
    }
    
    return 0;
}
