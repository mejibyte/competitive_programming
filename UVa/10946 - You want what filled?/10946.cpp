#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

typedef pair<char, int> hole;

struct holeCompare{
  bool operator() (const hole &a, const hole &b) const{
    return (a.second < b.second) ||
      (a.second == b.second && a.first > b.first);
  }
};

char g[50][50];
bool visited[51][51];
int r,c;

int di[] = {-1, 0, 1,  0};
int dj[] = { 0, 1, 0, -1};

int dfs(const int &i,const int &j){
  int result = 1;
  visited[i][j] = true;
  for (int k = 0; k<4; ++k){
    int iNew, jNew;
    iNew = i + di[k];
    jNew = j + dj[k];
    if (0 <= iNew && iNew < r &&
	0 <= jNew && jNew < c &&
	!visited[iNew][jNew] &&
	g[i][j] == g[iNew][jNew]){

      result += dfs(iNew, jNew);
    }
  }  
  return result;
}


int main(){
  int problemNo = 1;
  while (cin >> r >> c && (r | c)){
    for (int i=0; i<r; ++i){
      for (int j=0; j<c; ++j){
	cin >> g[i][j];
	visited[i][j] = false;
      }
    }

    multiset<hole, holeCompare> holes;
    for (int i=0; i<r; ++i){
      for (int j=0; j<c; ++j){
	if (!visited[i][j] && g[i][j] != '.'){
	  holes.insert(hole(g[i][j], dfs(i,j)));
	}
      }
    }
    cout << "Problem " << problemNo++ << ":" << endl;
    for (multiset<hole>::reverse_iterator i = holes.rbegin(); i != holes.rend(); ++i){
      cout << i->first << " " << i->second << endl;
    }
  }
  return 0;
}
