#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

#define D(x) cout << #x " = " << (x) << endl
using namespace std;

const int MAXN = 105;

int dist(int x1, int y1,    int x2, int y2){
  int dx = x1 - x2;
  int dy = y1 - y2;
  return dx * dx + dy * dy;
}

char mat[MAXN][MAXN];
typedef pair<int, int> point;

int rows, cols;
vector<point> people, chairs;

int chairFor[MAXN];
vector<int> peopleFor[MAXN];

int dist(int guy, int chair){
  return dist(people[guy].first, people[guy].second, chairs[chair].first, chairs[chair].second);  
}

int main(){
  cin >> rows >> cols;
  for (int i = 0; i < rows; ++i){
    for (int j = 0; j < cols; ++j){
      cin >> mat[i][j];
      if (mat[i][j] == 'X') people.push_back(point(i, j));
      if (mat[i][j] == 'L') chairs.push_back(point(i, j));
    }
  }

  for (int i = 0; i < people.size(); ++i){
    chairFor[i] = -1;
  }
  
  vector<pair<int, pair<int, int> > > options;
  for (int i = 0; i < people.size(); ++i){
    for (int j = 0; j < chairs.size(); ++j){
      options.push_back(make_pair(dist(i, j), make_pair(i, j)));
    }
  }
  
  sort(options.begin(), options.end());
  for (int k = 0; k < options.size(); ++k){
    int d = options[k].first;
    int guy = options[k].second.first;
    int chair = options[k].second.second;
    if (chairFor[guy] != -1) continue; //already seated
    if (peopleFor[chair].size() == 0 ||
	dist(peopleFor[chair][0], chair) == d){
      chairFor[guy] = chair;
      peopleFor[chair].push_back(guy);
    }
  }
  
  // for (int i = 0; i < people.size(); ++i){
  //   D(chairFor[i]);
  // }
 
  int ans = 0;
  for (int c = 0; c < chairs.size(); ++c){
    ans += (peopleFor[c].size() > 1);
  }
  cout << ans << endl;
  return 0;
}
