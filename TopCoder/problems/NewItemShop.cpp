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

class NewItemShop {
  public:
  double getMaximum(int swords, vector <string> customers);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; string Arr1[] = { "8,1,80 16,100,11", "12,10,100" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 19.0; verify_case(0, Arg2, getMaximum(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 2; string Arr1[] = { "8,1,80 16,100,11", "12,10,100" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 21.8; verify_case(1, Arg2, getMaximum(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 1; string Arr1[] = { "0,90,25 2,90,25 4,90,25 6,90,25", "7,100,80" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 90.0; verify_case(2, Arg2, getMaximum(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 3; string Arr1[] = { "17,31,41 20,59,26 23,53,5", "19,89,79", "16,32,38 22,46,26", "18,43,38 21,32,7" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 135.5121414; verify_case(3, Arg2, getMaximum(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 5; string Arr1[] = { "1,1,10", "2,2,9", "3,3,8", "4,4,7", "5,5,6", "6,6,5", "7,7,4", "8,8,3", "9,9,2", "10,10,1" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 2.1999744634845344; verify_case(4, Arg2, getMaximum(Arg0, Arg1)); }

// END CUT HERE

};

double P[30][30];
int C[30][30];

vector< int > clientAtHour;
vector< int > maskIndex;

bool bitset(int mask, int which) {
    return !!( mask & (1 << which) );
}

map<unsigned int, double> memo;

unsigned int getHash(unsigned int k, unsigned int h, unsigned int visited) {
    return (k << 19) + (h << 13) + visited;
}

double f(int k, int h, int visited) {
    if (k == 0) return 0.0;
    if (h > 23) return 0.0;
    
    long long hash = getHash(k, h, visited);
    if (memo.count(hash) > 0){
        return memo[hash];
    }
    
    int client = clientAtHour[h];
    if (client == -1) return f(k, h+1, visited);
    
    if (maskIndex[client] != -1 && bitset(visited, maskIndex[client])) return f(k, h+1, visited);
        
    int visitedPlusThisGuy = (maskIndex[client] == -1 ? visited : visited | (1 << maskIndex[client]));

    double p = P[client][h];
    double answer = f(k, h + 1, visited) * (1.0 - p);
    answer += p * max(f(k, h + 1,  visitedPlusThisGuy),
                  f(k - 1, h + 1, visitedPlusThisGuy) + C[client][h]);

    return memo[hash] = answer;
}

double NewItemShop::getMaximum(int swords, vector <string> customers) {
    clientAtHour = vector< int >(24, -1);
    maskIndex = vector< int >(customers.size());
    memo.clear();

    int currentIndex = 0;
	for (int i = 0; i < customers.size(); ++i){
		stringstream sin(customers[i]);
		string x;
		
        int sumP = 0;
        
        int count = 0;
		while (sin >> x) {
            count++;
			//x == t c p
			for (int j = 0; j < x.size(); ++j) if (x[j] == ',') x[j] = ' ';
			stringstream tokens(x);
			int t, c, p;
			tokens >> t >> c >> p;
			
            clientAtHour[t] = i;
            P[i][t] = (1.0L * p / (100 - sumP));
            C[i][t] = c;
            
            sumP += p;
		}
        maskIndex[i] = (count > 1 ? currentIndex++ : -1);
	}

	return f(swords, 0, 0);
}

// BEGIN CUT HERE
int main(){
    NewItemShop ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
