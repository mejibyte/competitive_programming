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

int start[8][8], end[8][8], cur[8][8];

int di[] = {-1, +1, +0, +0};
int dj[] = {+0, +0, -1, +1};

typedef unsigned long long int board;

#define outside(i, j) ((i) < 0 or (i) >= 8 or (j) < 0 or (j) >= 8)

board make_board(int b[8][8]){
    board ans = 0ULL;
    for (int i = 0; i < 8; ++i){
        for (int j = 0; j < 8; ++j){
            if (b[i][j]){
                ans |= (1ULL << (i * 8 + j));
            }
        }
    }
    return ans;
}

void unmake_board(board b, int out[8][8]){
    for (int i = 0; i < 8; ++i){
        for (int j = 0; j < 8; ++j){
            out[i][j] = 0;
        }
    }
    for (int i = 0; i < 8; ++i){
        for (int j = 0; j < 8; ++j){
            if (b & (1ULL << (i * 8 + j))){
                out[i][j] = true;
            }
        }
    }
}

void explore(board s, set<board> &seen) {
    queue<board> boards;
    queue<char> distance;
    
    boards.push(s);
    distance.push(0);
    
    while (boards.size() > 0) {
        board b = boards.front(); boards.pop();
        char d = distance.front(); distance.pop();
        
        if (d == 4) continue; // Too far
        
        unmake_board(b, cur);
        
        //printf("d is %d\n", (int)d);
        //printf("cur is\n"); for (int i = 0; i < 8; ++i){ for (int j = 0; j < 8; ++j){ printf("%d ", cur[i][j]); } puts(""); } puts("");

        for (int i = 0; i < 8; ++i){
            for (int j = 0; j < 8; ++j){
                if (!cur[i][j]) continue;
                for (int k = 0; k < 4; ++k){
                    int ni = i + di[k];
                    int nj = j + dj[k];
                    if (outside(ni, nj)) continue;
                    if (cur[ni][nj]){ //taken, let's move one extra cell
                        ni += di[k];
                        nj += dj[k];
                        if (outside(ni, nj)) continue;
                        if (cur[ni][nj]) continue;
                    }
                    assert(!cur[ni][nj]);
                    assert(cur[i][j]);
                    swap(cur[ni][nj], cur[i][j]);

                    board cur_mask = make_board(cur);
                    if (seen.count(cur_mask) == 0){
                        // not seen, let's enqueue this new state
                        seen.insert(cur_mask);
                        boards.push(cur_mask);
                        distance.push(d + 1);
                    }
                    swap(cur[ni][nj], cur[i][j]);
                }
            }
        }
    }
}

int main(){
    int T;
    scanf("%d", &T);
    while (T--){
        for (int i = 0; i < 8; ++i){
            for (int j = 0; j < 8; ++j){
                start[i][j] = end[i][j] = 0;
            }
        }
                
        for (int i = 0; i < 4; ++i){
            int r, c;
            if (scanf("%d%d", &r, &c) != 2) return 0;
            r--, c--;
            assert(!start[r][c]);
            start[r][c]++;
        }
        for (int i = 0; i < 4; ++i){
            int r, c;
            if (scanf("%d%d", &r, &c) != 2) return 0;
            r--, c--;
            assert(!end[r][c]);
            end[r][c]++;
        }

        set<board> s1;
        set<board> s2;
        s1.insert(make_board(start));
        s2.insert(make_board(end));
        
        explore(make_board(start), s1);
        explore(make_board(end), s2);

        //printf("s1.size = %d\n", s1.size());

        bool ans = false;
        foreach(x, s1) {
            if (s2.count(*x) > 0){
                ans = true;
                break;
            }
        }
        puts(ans ? "YES" : "NO");
    }
    return 0;
}