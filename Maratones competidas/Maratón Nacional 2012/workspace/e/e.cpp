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

const int MAXN = 10005;
int efes[MAXN];
int des[MAXN];
const string grid [10][3] = 
         {{ "._.",
            "|.|",
            "|_|",
          },
          { "...",
            "..|",
            "..|"
        },
        {   "._.",
            "._|",
            "|_."
        },
        {   "._.",
            "._|",
            "._|"
        },
        {   "...",
            "|_|",
            "..|"
        },
        {   "._.",
            "|_.",
            "._|"
        },
        {   "._.",
            "|_.",
            "|_|"
        },
        {   "._.",
            "..|",
            "..|"
        },
        {   "._.",
            "|_|",
            "|_|"
        },
        {   "._.",
            "|_|",
            "._|"
        }
    };

char line (int d, int f, int x, int y, bool canbemiddle = true)  {
    char ret;
   // D(d);D(x);D(y);
    y = 2-y;
    if (x == 0) ret= grid[d][y][0];
    else if (x == (f+1))ret= grid[d][y][2];
    else if (canbemiddle) ret= grid[d][y][1];
    else ret = '.';
   // D(ret);
    return ret;
}


char xy (int d, int f, int x, int y) {
    if (y > 2*f) return '.';
    if (y == 0) return line(d,f,x,0);
    if (y < f) return line(d,f,x,0,false);
    if (y == f) return line(d,f,x,1);
    if (y < 2*f) return line(d,f,x,1,false);
    return line(d,f,x,2);   
}

pair <int, int> find_digit(int x){
    int digit = -1;
    int col = -1;
    while (x > col){
        digit++;
        col += efes[digit] + 2;
        if (x <= col) return (make_pair(digit, x - (col - (efes[digit] + 2)+1)));
        col++;
        if (x == col) return (make_pair(-1, 1));            
    }
    assert(false);  
}

int main () {
    freopen("lcd.in", "r", stdin);
    int n;
    while (cin >> n){
        if (n == 0) break;
        
        for (int i = 0; i < n; i++){
            cin >> des[i] >> efes[i];    
        }
        int q;
        cin >> q;
        for (int i = 0; i < q; i++){
            int x, y;
            cin >> x >> y;
            
            pair <int, int> digit = find_digit(x);
            if (digit.first == -1) {
                cout << "." << endl;
                continue;
            }
            //cout<<"is in digit : "<<des[digit.first]<<endl;
            int d = digit.first;
            x = digit.second;
            cout << xy(des[d], efes[d], x, y) << endl;
        }
    }

    return 0;
}
