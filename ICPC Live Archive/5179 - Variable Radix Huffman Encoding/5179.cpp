// Andrés Mejía
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

struct Item {
  set<char> characters;
  int weight;
};

// Returns true if item b should be removed from the priority queue before a.
bool operator < (const Item &a, const Item &b) {
  if (a.weight != b.weight) return a.weight > b.weight;
  return *a.characters.begin() > *b.characters.begin();
}


int main() {
    int R, N, Set = 1;
    while (cin >> R >> N and R > 0) {
      vector<int> f(N);
      for (int i = 0; i < N; ++i) cin >> f[i];
      priority_queue<Item> q;
      for (int i = 0; i < N; ++i) {
        Item t = {{char('A' + i)}, f[i]};
        q.push(t);
      }

      // Ficticious characters.
      while (R > 2 and (q.size() % (R - 1)) != 1) {
        Item t = {{'^'}, 0}; // ^ is lexicographically larger than Z
        q.push(t);
      }

      map<char, string> code;

      while (q.size() > 1) {
        Item new_item = {{}, 0};

        for (int r = 0; r < R; ++r) {
          Item next = q.top();
          q.pop();

          for (char c : next.characters) {
            code[c] += '0' + r;
            new_item.characters.insert(c);
          }
          new_item.weight += next.weight;
        }

        q.push(new_item);
      }

      int weighted_sum = 0;
      int total_chars = 0;
      for (int i = 0; i < N; ++i) {
        total_chars += f[i];
        weighted_sum += f[i] * code['A' + i].size();
      }
      printf("Set %d; average length %.2f\n", Set++, 1.0 * weighted_sum / total_chars);
      for (int i = 0; i < N; ++i) {
        reverse(code['A' + i].begin(), code['A' + i].end());
        printf("    %c: %s\n", 'A' + i, code['A' + i].c_str());
      }
      printf("\n");
    }

    return 0;
}
