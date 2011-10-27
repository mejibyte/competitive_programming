#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

#define D(x) cout << #x " = " << (x) << endl
using namespace std;

const int MAXN = 1005;
char mat[MAXN][MAXN];
typedef pair<int, int> point;

int dist(int x1, int y1, int x2, int y2){
  int dx = abs(x1 - x2);
  int dy = abs(y1 - y2);
  return max(dx, dy);
}
int sum(const vector<point> &p){
  int n = p.size(), ans = 0;
  for (int i = 0; i < n; ++i){
    for (int j = i + 1; j < n; ++j){
      ans += dist(p[i].first, p[i].second, p[j].first, p[j].second);
    }
  }
  return ans;
}

int main(){
  int rows, cols;
  cin >> rows >> cols;
  
  vector<point> a, b;
  for (int i = 0; i < rows; ++i){
    for (int j = 0; j < cols; ++j){
      cin >> mat[i][j];
      if (mat[i][j] == 'M') a.push_back(point(i, j));
      if (mat[i][j] == 'S') b.push_back(point(i, j));
    }
  }
  
  cout << sum(a) << " " << sum(b) << endl;
  return 0;
}
