#include <iostream>
#include <queue>
using namespace std;

bool v[11][11][27];
int dp[11*11*27][11][11][27];
char g[11][11];

struct state{
    int i, j, w;
    char last;
    state(){} state(int I, int J, char L, int W) : i(I), j(J), last(L), w(W) {}
};

int n;
char final;
int di[] = {-1, +1, +0, +0};
int dj[] = {+0, +0, +1, -1};

#define inside(i, j) (0 <= i && i < n && 0 <= j && j < n)
#define D(x) cout << #x " es " << x << endl
#define unchar(c) ((c)-'A')

const int mod = 20437;

void bfs(int si, int sj){
     memset(v, 0, sizeof v);
     memset(dp, 0, sizeof dp);
     dp[0][si][sj][0] = 1;
     
     queue<state> q;
     q.push(state(si, sj, 'A', 0));
     while (q.size()){
         int i = q.front().i, j = q.front().j, w = q.front().w;
         char last = q.front().last;
         //printf("popped (%d, %d, %c, %d)\n", i, j, last, w);
         q.pop();
         if (v[i][j][unchar(last)]) continue;
         v[i][j][unchar(last)] = true;
         
         if (g[i][j] == final){
            //Llegue
            cout << w << " " << (dp[w][i][j][unchar(last)] % mod) << endl;
            return;
         }
         int new_paths = dp[w][i][j][unchar(last)];
         if (g[i][j] == last) g[i][j] = '.', last++;
         //D(new_paths);
         for (int k=0; k<4; ++k){
             int ni = i + di[k], nj = j + dj[k];
             if (inside(ni, nj) && !v[ni][nj][unchar(last)] && (g[ni][nj] == '.' || g[ni][nj] == last)){
                dp[w+1][ni][nj][unchar(last)] = ((dp[w+1][ni][nj][unchar(last)])%mod + (new_paths)%mod)%mod;
                q.push(state(ni, nj, last, w+1));
             }
         }
     }
     cout << "Impossible" << endl;
}

int main(){
    int C=1;
    while (cin >> n && n){
       int si, sj;
       final = 'A';
       for (int i=0; i<n; ++i){
           for (int j=0; j<n; ++j){
               cin >> g[i][j];
               if (g[i][j] == 'A') si = i, sj = j;
               if (g[i][j] > final) final = g[i][j];
           }
       }
       cout << "Case " << C++ << ": ";
       bfs(si, sj);
    }
    return 0;
}
