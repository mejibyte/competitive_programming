// Equipo Ultimatum

using namespace std;
# include <algorithm>
# include <iostream>
# include <iterator>
# include <sstream>
# include <fstream>
# include <cassert>
# include <cstdlib>
# include <string>
# include <cstring>
# include <cstdio>
# include <vector>
# include <cmath>
# include <queue>
# include <stack>
# include <map>
# include <set>

#define For(i, a, b) for (int i = (a); i < (b); i++)
#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); x != v.end(); x++)
#define D(x) cout << #x  " = " << (x) << endl

const double EPS = 1e-9;
int cmp (double x, double y = 0, double tol = EPS){
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

map<char, int> lettervalue;

string dig_to_roman(char d, char c, char u, int x) {
    string ans = "";
    if (d == 0) return ans;
    if (x == 9) {
        ans += u;
        ans += d;
        return ans;   
    }
    if (x == 4) {
        ans += u;
        ans += c;
        return ans;
    }
    if (x < 5) {
        while(x--)ans+=u;
        return ans;   
    }
    ans += c;
    while(x > 5) {
        x--;
        ans += u;   
    }
}

string to_good_roman(int x) {
    assert(x < 4000);
    int pow = 1000;
    string ans = "";
    ans += dig_to_roman('z','z','M',(x/pow)%10);
    pow /= 10;
    ans += dig_to_roman('M','D','C',(x/pow)%10);
    pow /= 10;
    ans += dig_to_roman('C','L','X',(x/pow)%10);
    pow /= 10;
    ans += dig_to_roman('X','V','I',(x/pow)%10);
    return ans;
}

int tiberius(const string &s) {
    int ans = 0;
    for (int i = 0; i < s.size(); ++i) {
        int sign = +1;

        int next = i + 1;
        while (next < s.size() and s[i] == s[next]) next++;
        
        if (next < s.size() and lettervalue[s[next]] > lettervalue[s[i]]) sign = -1;
        ans += sign * lettervalue[s[i]];
    }
    assert(ans <= 3999);
    return ans;
}

int SZ(const string &s) {
    return (int)s.size();
}

pair<int, int> convert(const string &from, const string &to) {
    int e = SZ(from);
    int c = SZ(to);
    
 //   D(from); D(to);
    
    for (int at = SZ(from); at + SZ(to) - 1 >= -1; --at) {
        int ne = 0;
        int nc = 0;
        
        
        for (int k = min(0, at); k <= max(SZ(from) - 1, at + SZ(to) - 1); ++k) {
            char ff = '*';
            char tt = '*';
            if (0 <= k and k <= SZ(from) - 1) ff = from.at(k);
            if (at <= k and k <= at + SZ(to) - 1) tt = to.at(k - at);
            
         
            
            if (ff == '*' and tt == '*') {
              continue; // nada que hacer
            }
        
            if (ff == '*' and tt != '*') {
                nc++; // cavo en to
                continue;
            }
            if (ff != '*' and tt == '*') {
                ne++; // borro en from
               continue;
            }
            assert(ff != '*' and tt != '*');
            if (ff == tt) {
               continue; // nada
            }   
            // borro y cavos
            ne++;
            nc++;   
        }
        
        if (ne + nc < e + c or (ne + nc == e + c and ne < e)) {
            e = ne;
            c = nc;
        }
    }
    
    return make_pair(e, c);
}


int main () {
    freopen("imperial.in", "r", stdin);
    
    lettervalue['I'] = 1;
    lettervalue['V'] = 5;
    lettervalue['X'] = 10;
    lettervalue['L'] = 50;
    lettervalue['C'] = 100;
    lettervalue['D'] = 500;
    lettervalue['M'] = 1000;
    
    string old;
    while (cin >> old) {
        if (old == "*") break;
        int t = tiberius(old);
        string new_value = to_good_roman(t);
        
        pair<int, int> ans = convert(old, new_value);
        cout << ans.first << " " << ans.second << endl;
    }
    
    return 0;
}
