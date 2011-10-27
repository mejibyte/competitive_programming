#include <iostream> 
#include <sstream> 
#include <string> 
#include <vector> 
#include <deque> 
#include <queue> 
#include <set> 
#include <map> 
#include <algorithm> 
#include <functional> 
#include <utility> 
#include <cmath> 
#include <cstdlib> 
#include <ctime> 

using namespace std; 

#define REP(i,n) for((i)=0;(i)<(int)(n);(i)++) 

#define INF (1<<29) 
typedef long long ll; 

int X,Y; 
int dx[]={1,-1,0,0},dy[]={0,0,1,-1}; 
vector <string> maze; 
vector <pair <int, int> > L,F,R; 

queue <int> q; 
priority_queue <pair <int, pair <int, int> > > pq; 
bool used[60][60]; 

int dist2[2][60][60]; 
int dist[60][60]; 

class MeetInTheMaze{ 
  public: 
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
      
   
  ll gcd(ll x, ll y){ 
    return x ? gcd(y%x,x) : y; 
  } 
   
  void bfs(int id, int sx, int sy){ 
    int i,j; 
     
    REP(i,X) REP(j,Y) dist2[id][i][j] = INF; 
    q.push(sx); q.push(sy); dist2[id][sx][sy] = 0; 
     
    while(!q.empty()){ 
      int x = q.front(); q.pop(); int y = q.front(); q.pop(); int d = dist2[id][x][y]; 
      REP(i,4){ 
        int x2 = x + dx[i], y2 = y + dy[i]; 
        if(x2 >= 0 && x2 < X && y2 >= 0 && y2 < Y && dist2[id][x2][y2] == INF && maze[x2][y2] != '#'){ 
          dist2[id][x2][y2] = d + 1; 
          q.push(x2); q.push(y2); 
        } 
      } 
    } 
  } 
   
  void add(int x, int y, int d){ 
    if(x >= 0 && x < X && y >= 0 && y < Y && d < dist[x][y] && maze[x][y] != '#'){ 
      dist[x][y] = d; 
      pq.push(make_pair(-d,make_pair(x,y))); 
    } 
  } 
   
  ll func(void){ 
    int i,j; 
     
    REP(i,X) REP(j,Y) dist[i][j] = INF; 
    REP(i,X) REP(j,Y) used[i][j] = false; 
     
    REP(i,X) REP(j,Y) add(i,j,dist2[0][i][j]+dist2[1][i][j]); 
    while(!pq.empty()){ 
      int x = pq.top().second.first, y = pq.top().second.second, d = -pq.top().first; pq.pop(); 
      if(used[x][y]) continue; used[x][y] = true; 
      REP(i,4) add(x+dx[i],y+dy[i],d+1); 
    } 
     
    ll ans = 0; 
    REP(i,L.size()){ 
      int x = L[i].first, y = L[i].second; 
      if(dist[x][y] == INF) return -1; 
      ans += dist[x][y]; 
    } 
     
    return ans; 
  } 

  string getExpected(vector <string> _maze){ 
    int i,j; 
     
    maze = _maze;
    L.clear(); F.clear(); R.clear();
     
    X = maze.size(); Y = maze[0].length(); 
    REP(i,X) REP(j,Y){ 
      if(maze[i][j] == 'L') L.push_back(make_pair(i,j)); 
      if(maze[i][j] == 'F') F.push_back(make_pair(i,j)); 
      if(maze[i][j] == 'R') R.push_back(make_pair(i,j)); 
    } 
     
    ll ans1 = 0; 
    ll ans2 = L.size() * F.size() * R.size(); 
     
    REP(i,F.size()) REP(j,R.size()){ 
      bfs(0,F[i].first,F[i].second); 
      bfs(1,R[j].first,R[j].second); 
      ll tmp = func(); 
      if(tmp == -1) return ""; 
      ans1 += tmp; 
    } 
     
    ll g = gcd(ans1,ans2); 
    ans1 /= g; ans2 /= g; 
    stringstream ss; 
    ss << ans1 << "/" << ans2; 
     
    string ans = ss.str(); 
    return ans; 
  } 

}; 

// BEGIN CUT HERE
int main(){
    MeetInTheMaze ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
