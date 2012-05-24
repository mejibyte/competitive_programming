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
#include <bitset>
#include <cmath>
#include <queue>
#include <deque>
#include <stack>
#include <list>
#include <map>
#include <set>

#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << (x) << endl

class AntsMeet {
  public:
  int countAnts(vector <int> x, vector <int> y, string direction);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {0,10,20,30}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,10,20,30}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "NWNE"; int Arg3 = 2; verify_case(0, Arg3, countAnts(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {-10,0,0,10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,-10,10,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "NEWS"; int Arg3 = 0; verify_case(1, Arg3, countAnts(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {-1,-1,-1,0,0,0,1,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-1,0,1,-1,0,1,-1,0,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "ESEWNNEWW"; int Arg3 = 4; verify_case(2, Arg3, countAnts(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {4,7,6,2,6,5,7,7,8,4,7,8,8,8,5,4,8,9,1,5,9,3,4,0,0,1,0,7,2,6,9,6,3,0,5,5,1,2,0,4,9,7,7,1,8,1,9,2,7,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,3,0,6,8,4,9,0,5,0,2,4,3,8,1,5,0,7,3,7,0,9,8,1,9,4,7,8,1,1,6,6,6,2,8,5,1,9,0,1,1,1,7,0,2,5,4,7,5,3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "SSNWSWSENSWSESWEWSWSENWNNNESWSWSWWSSWEEWWNWWWNWENN" ; int Arg3 = 25; verify_case(3, Arg3, countAnts(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arr0[] = {478,-664,759,434,-405,513,565,-396,311,-174,56,993,251,-341,993,-112,242,129,383,513,-78,-341,-148,129,423
,493,434,-405,478,-148,929,251,56,242,929,-78,423,-664,802,251,759,383,-112,-591,-591,-248,660,660,735,493}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-186,98,948,795,289,-678,948,-170,-195,290,-354,-424,289,-157,-166,150,706,-678,684,-294,-234,36,36,-294,-216
,-234,427,945,265,-157,265,715,275,715,-186,337,798,-170,427,706,754,961,286,-216,798,286,961,684,-424,337}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "WNSNNSSWWWEENWESNSWSWSEWWEWEWWWNWESNSSNNSNNWWWNESE"; int Arg3 = 44; verify_case(4, Arg3, countAnts(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

string compass = "NSEW";

enum { N, S, E, W };

int dr[] = {-1, +1, +0, +0};
int dc[] = {+0, +0, +1, -1};

struct Ant {
    int r, c;
    int direction;
    
    void move() {
        r += dr[direction];
        c += dc[direction];
    }
};

bool special_case(Ant aa, Ant bb) {
    // special case
    if (bb.direction == E) swap(aa, bb);
    if (aa.direction == E and bb.direction == W and aa.r == bb.r and aa.c + 1 == bb.c) return true;
    
    if (bb.direction == S) swap(aa, bb);
    if (aa.direction == S and bb.direction == N and aa.c == bb.c and aa.r + 1 == bb.r) return true;
    return false;
}
    
bool will_collide(Ant aa, Ant bb) {
    aa.move(); bb.move();
    if (aa.r == bb.r and aa.c == bb.c) return true; // easy case

    return false;
}

int AntsMeet::countAnts(vector <int> x, vector <int> y, string direction) {
    vector<Ant> ants(x.size());
    for (int i = 0; i < x.size(); ++i) {
        ants[i].r = -y[i];
        ants[i].c = x[i];
        ants[i].direction = compass.find(direction[i]);
        assert(ants[i].direction >= 0);
    }
    for (int t = 0; t <= 2005; ++t) {
        vector<Ant> next_ants;
        vector<bool> alive(ants.size(), true);
        int n = ants.size();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i != j and special_case(ants[i], ants[j])){
                    alive[i] = alive[j] = false;
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            if (alive[i]) next_ants.push_back(ants[i]);
        }
        
        ants.assign(next_ants.begin(), next_ants.end());
        next_ants.clear();
        n = ants.size();
        alive.assign(n, true);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i != j and will_collide(ants[i], ants[j])){
                    alive[i] = alive[j] = false;
                }
            }
        }
        
        for (int i = 0; i < n; ++i) {
            ants[i].move();
            if (alive[i]) next_ants.push_back(ants[i]);
        }
        
        ants.assign(next_ants.begin(), next_ants.end());
    }
    return ants.size();
}

// BEGIN CUT HERE
int main(){
    AntsMeet test;
    test.run_test(-1);
    return 0;
}
// END CUT HERE
