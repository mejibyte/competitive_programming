#include <iostream>
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
int sits[MAXN];
typedef pair<int, int> point;

int rows, cols;
vector<point> people, chairs;

int someoneCloser(int guy, int chair){
  int D = dist(people[guy].first, people[guy].second, chairs[chair].first, chairs[chair].second);
  for (int i = 0; i < people.size(); ++i){
    if (i == guy) continue;
    int d = dist(people[i].first, people[i].second, chairs[chair].first, chairs[chair].second);
    if (d < D) return true;
  }
  return false;
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
    //figure out in what chair this guy sits
    vector<pair<int, int> > options;
    for (int j = 0; j < chairs.size(); ++j){
      options.push_back(make_pair(dist(people[i].first, people[i].second, chairs[j].first, chairs[j].second), j));
    }
    sort(options.begin(), options.end());
    sits[i] = -1; //no chair, yet
    for (int j = 0; j < options.size(); ++j){
      if (someoneCloser(i, j)) continue;
      else{
	sits[i] = options[j].second;
	break;
      }
    }
  }
  
  for (int i = 0; i < people.size(); ++i){
    cout << sits[i] << endl;
  }
  
  return 0;
}
