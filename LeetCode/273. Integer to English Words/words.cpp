// Andrés Mejía
#include <unordered_map>
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
#include <bitset>
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
using namespace std;

////////////// Prewritten code follows. Look down for solution. ////////////////
#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cerr << #x " is " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
////////////////////////// Solution starts below. //////////////////////////////

/*
1 digit: map
2 digit: 10-19: map, 20-99: map + f(1)
3 digit: one hundred + f(1)
4 digit: one thousand
5 digit: ten thousand
6 digit: one hundred thousand
7 digit: one million
8 digit: ten million
9 digit: one hundred million
10 digit: one billion

0-9 -> Zero
10-19 -> ten, eleven, twelve, ...
20
21, 29 -> Twenty One
100
900
1000
10_000
123 -> "One Hundred Twenty Three"
12345 -> "Twelve Thousand Three Hundred Forty Five"
1234567 -> "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"
*/

map<int, string> name = {
   {0, "Zero"},
   {1, "One"},
   {2, "Two"},
   {3, "Three"},
   {4, "Four"},
   {5, "Five"},
   {6, "Six"},
   {7, "Seven"},
   {8, "Eight"},
   {9, "Nine"},
   {10, "Ten"},
   {11, "Eleven"},
   {12, "Twelve"},
   {13, "Thirteen"},
   {14, "Fourteen"},
   {15, "Fifteen"},
   {16, "Sixteen"},
   {17, "Seventeen"},
   {18, "Eighteen"},
   {19, "Nineteen"},
   {20, "Twenty"},
   {30, "Thirty"},
   {40, "Forty"},
   {50, "Fifty"},
   {60, "Sixty"},
   {70, "Seventy"},
   {80, "Eighty"},
   {90, "Ninety"},
 };

class Solution {
public:
    string numberToWords(long long n) {
      if (name.count(n)) return name[n];
      if (n <= 99) {
        int d = n / 10;
        int remain = n - d * 10;
        return name[d * 10] + rest(remain);
      }

      if (n <= 999) {
        int d = n / 100;
        int remain = n - d * 100;
        return numberToWords(d) + " Hundred" + rest(remain);
      }
      if (n <= 999999) {
        int d = n / 1000;
        int remain = n - d * 1000;
        return numberToWords(d) + " Thousand" + rest(remain);
      }
      if (n <= 999999999) {
        int d = n / 1000000;
        int remain = n - d * 1000000;
        return numberToWords(d) + " Million" + rest(remain);
      }
      if (n <= 999999999999L) {
        int d = n / 1000000000;
        int remain = n - d * 1000000000;
        return numberToWords(d) + " Billion" + rest(remain);
      }
    }
private:

    string rest(int n) {
      if (n == 0) return "";
      return " " + numberToWords(n);
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */

int main() {
  Solution s;
  for (int i = 0; i <= 99; ++i) {
    D(s.numberToWords(i));
  }
  D(s.numberToWords(456));
  D(s.numberToWords(465));
  D(s.numberToWords(400));
  D(s.numberToWords(320));
  D(s.numberToWords(1000));
  D(s.numberToWords(2017));
  D(s.numberToWords(22001));
  D(s.numberToWords(130457));
  D(s.numberToWords(1234567));
  D(s.numberToWords(1000000));
  D(s.numberToWords(10000000));
  D(s.numberToWords(100000000));
  D(s.numberToWords(1000000000));
  D(s.numberToWords(1111111111));


  return 0;
}


