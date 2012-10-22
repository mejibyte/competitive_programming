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

bool M [105][105];
bool Z [105][105];


pair<int, int> parse(const string &s) {
    int row = s[0] - 'A';
    stringstream sin(s.substr(1));
    int col;
    sin >> col;
    return make_pair(row, col);
}

int main () {
    freopen("cinema.in", "r", stdin);
    int R, C;
    while (cin >> R >> C){
        if (R == 0 and C == 0) break;
        for (int i = 0; i <= R; i++){
            for (int j = 0; j <= C; j++){
                M[i][j] = Z[i][j] = 0;    
            }    
        }
        
        int p; cin >> p;
        
        for (int k = 0; k < p; k++){
            string s; cin >> s;
            int row = s[0] - 'A';
            stringstream sin(s.substr(1));
            int col;
            sin >> col;
            char c; cin >> c;
            if (c == '+') M[row][col] = 1;
            else M[row][col-1] = 1;
        }
        
        cin >> p;
        
        for (int k = 0; k < p; k++){
            string s; cin >> s;
            int row = s[0] - 'A';
            stringstream sin(s.substr(1));
            int col;
            sin >> col;
            Z[row][col] = 1;
        }
        bool can = true;
        for (int i = 0; i < R; i++){
            for (int j = 1; j <= C; j++){
                if (Z[i][j] == 1){
                    if (M[i][j - 1] == 0){
                        M[i][j-1] = 1;
                    }else if (M[i][j] == 0){
                        M[i][j] = 1;    
                    }else{
                        can = false;
                        break;
                    }  
                }    
            }
            if (!can) break;
        }   
        
        if (can) cout << "YES" << endl;
        else puts("NO");
            
    }
    return 0;
}
