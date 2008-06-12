#include <iostream>
#include <string>

using namespace std;

int     di[] = {     0,      -1,       0};
int     dj[] = {    -1,       0,       1};
string dir[] = {"left", "forth", "right"};

char g[9][9];

string route = "@IEHOVA#";


int main(){
  int n;
  cin >> n;
  while (n--){
    pair<int,int> start;
    int r, c;
    cin >> r >> c;
    for (int i=0; i<r; ++i){
      for (int j=0; j<c; ++j){
	cin >> g[i][j];
	if (g[i][j] == '@') start = make_pair(i,j);
      }
    }

    int i = start. first;
    int j = start.second;
    string res = "";
    for (int k = 1; k < 8; ++k){
      for (int l = 0; l < 3; ++l){
	int ni = i + di[l];
	int nj = j + dj[l];
	if (0 <= ni && ni < r && 0 <= nj && nj < c &&
	    g[ni][nj] == route[k]){
	  res += dir[l];
	  res += (k<7?" ":"");
	  i = ni;
	  j = nj;
	  break;
	}
      }
    }
    cout << res << endl;
  }
  return 0;
}
