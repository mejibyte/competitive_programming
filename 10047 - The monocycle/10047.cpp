#include <iostream>
#include <queue>

using namespace std;

int di[] = {-1, +0, +1, +0 };
int dj[] = {+0, +1, +0, -1 };
enum {green, black, red, blue, white};
enum {up, right, down, left};

char g[30][30];

struct state{
    int i, j, color, dir, w;
    state(){}
    state(int I, int J, int C, int D, int W) : i(I), j(J), color(C), dir(D), w(W) {}
};

bool visited[30][30][10][10];

int main(){
  //freopen("in.txt", "r", stdin);
    int rows, cols, C=1;
    while (cin >> rows >> cols && rows && cols){
        if (C > 1) cout << endl;
        pair<int, int> start, end;
        for (int i=0; i<rows; ++i){
            for (int j=0; j<cols; ++j){
                char c; cin >> g[i][j];
                if (g[i][j] == 'S') start = make_pair(i,j);
                if (g[i][j] == 'T') end = make_pair(i, j);
            }
        }

        cout << "Case #" << C++ << endl;

        memset(visited, 0, sizeof visited);
        queue<state> q;
        q.push(state(start.first, start.second, green, up, 0));
        bool solved = false;
        while (q.size()){
              int i = q.front().i, j = q.front().j, c = q.front().color, d = q.front().dir, w = q.front().w;
              q.pop();

              if (i == end.first && j == end.second && c == green){
                 cout << "minimum time = " << w << " sec" << endl;
                 solved = true;
                 break;
              }

              if ((0 <= i && i < rows && 0 <= j && j < cols) == false) continue;
              if (g[i][j] == '#') continue;
              if (visited[i][j][c][d]) continue;
              visited[i][j][c][d] = true;

              q.push(state(i, j, c, (d+1)%4, w+1 ));
              q.push(state(i, j, c, (d+3)%4, w+1 ));
              q.push(state(i + di[d], j + dj[d], (c+1)%5, d, w+1));
        }
        if (!solved) cout << "destination not reachable" << endl;
    }
    return 0;
}
