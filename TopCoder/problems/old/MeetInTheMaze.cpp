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

class MeetInTheMaze {
  public:
  string getExpected(vector <string> maze);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = { "#########", 
  "####F####", 
  "##L...R##", 
  "####L####", 
  "#########" }
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "9/2"; verify_case(0, Arg1, getExpected(Arg0)); }
	void test_case_1() { string Arr0[] = { "LR", 
  "RF" }
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "2/1"; verify_case(1, Arg1, getExpected(Arg0)); }
	void test_case_2() { string Arr0[] = { "..F.#...", 
  "L.F.#..L", 
  "..F.#...", 
  ".R.#..L.", 
  "...#....", 
  "..R#.L.." }
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = ""; verify_case(2, Arg1, getExpected(Arg0)); }
	void test_case_3() { string Arr0[] = { ".L..L..L..", 
  "..........", 
  "..........", 
  "..........", 
  "........R.", 
  "...R......", 
  "..........", 
  "..........", 
  "..........", 
  ".......F.." }
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "40/3"; verify_case(3, Arg1, getExpected(Arg0)); }
	void test_case_4() { string Arr0[] = { "#.#....#...#.#", 
  "#...#..#......", 
  ".L#...#R#..#F.", 
  "#...#......#..", 
  "#......#.....#", 
  ".R.....F....L.", 
  "##..#.......#.", 
  "#........##...", 
  ".F...##L#..#R#" }
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "362/27"; verify_case(4, Arg1, getExpected(Arg0)); }
	void test_case_5() { string Arr0[] = { "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLFLLLLLLLLLFLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLFFLLLLLLLLLLRLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLRLLLLLFLLLLLLLLLLLLLLF", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLF", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLFLLL", 
  "LLLLLLLLLLLRLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLRRL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLRLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLR", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLRLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLRLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLRLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLRLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLFFLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "FLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLRLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLRLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLFLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLFLLLLLLLLLRLLLLLLLLLLLLLLLLLLLRLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLFLLLLLLLLLLLLLLLLRLLLLLLLLLRLLLLLLLLLLLLRLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLRLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLFLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLFLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLFLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "FLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLRLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLFLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLFLLLLLLLLLLLLLLLLLLLLLL" }
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "210623/4100"; verify_case(5, Arg1, getExpected(Arg0)); }

// END CUT HERE

};

short dist[50][50][50][50];
int rows, cols;
int di[] = { -1, +1, +0, +0 };
int dj[] = { +0, +0, -1, +1 };

vector<string> maze;

bool valid(int r, int c) {
    return (0 <= r and r < rows and 0 <= c and c < cols and maze[r][c] != '#');
}

void fillDistance(int si, int sj) {
    if (!valid(si, sj)) return;    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            dist[si][sj][i][j] = (1 << 14);
        }
    }
    queue<int> q;
    dist[si][sj][si][sj] = 0;
    q.push(si); q.push(sj);
    while (q.size()) {
        int ci = q.front(); q.pop();
        int cj = q.front(); q.pop();
        for (int k = 0; k < 4; ++k) {
            int ni = ci + di[k];
            int nj = cj + dj[k];
            if (valid(ni, nj) and dist[si][sj][ci][cj] + 1 < dist[si][sj][ni][nj]) {
                dist[si][sj][ni][nj] = dist[si][sj][ci][cj] + 1;
                q.push(ni); q.push(nj);
            }
        }
    }
}

vector< pair<int, int> > R, F, L;

int d[50][50];

long long shortestPaths(int r, int f) {
    priority_queue< pair< int, pair <int, int > >, vector< pair<int, pair<int, int> > >, greater< pair<int, pair<int, int> > > > q;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            d[i][j] = dist[R[r].first][R[r].second][i][j] + dist[F[f].first][F[f].second][i][j];
            q.push(  make_pair(d[i][j], make_pair(i, j) )  );
        }
    }
    
    while (q.size()) {
        int cd = q.top().first, ci = q.top().second.first, cj = q.top().second.second;
        q.pop();
        
        if (cd > d[ci][cj]) continue;
        for (int k = 0; k < 4; ++k) {
            int ni = ci + di[k];
            int nj = cj + dj[k];
            if (valid(ni, nj) and d[ci][cj] + 1 < d[ni][nj]) {
                d[ni][nj] = d[ci][cj] + 1;
                q.push(   make_pair(d[ni][nj],   make_pair(ni, nj))  );
            }
        }
    }
    
    long long ans = 0;
    for (int l = 0; l < L.size(); ++l) {
        ans += d[L[l].first][L[l].second];
    }
    return ans;
}

string MeetInTheMaze::getExpected(vector <string> _maze) {
    maze = _maze;
    rows = maze.size();
    cols = maze[0].size();
    R.clear(); F.clear(); L.clear();
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            fillDistance(i, j);
            
            if (maze[i][j] == 'L') L.push_back(make_pair(i, j));
            if (maze[i][j] == 'R') R.push_back(make_pair(i, j));
            if (maze[i][j] == 'F') F.push_back(make_pair(i, j));
            
            for (int ii = 0; ii < rows; ++ii) {
                for (int jj = 0; jj < cols; ++jj) {
                    if (valid(i, j) and valid(ii, jj) and maze[i][j] != '.' and maze[ii][jj] != '.' and dist[i][j][ii][jj] >= (1 << 14)) {
                        return "";
                    }
                }
            }
        }
    }


    long long answer = 0;

    for (int r = 0; r < R.size(); ++r) {
        for (int f = 0; f < F.size(); ++f) {
            answer += shortestPaths(r, f);
        }
    }
    
    long long size = (long long)R.size() * (long long)F.size() * (long long)L.size();
    
    long long g = __gcd(answer, size);
    
    char s[100];
    sprintf(s, "%lld/%lld", answer / g, size / g);
    return string(s);
}

// BEGIN CUT HERE
int main(){
    MeetInTheMaze ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
