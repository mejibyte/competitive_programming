#include <iostream>
#include <set>
#include <queue>

using namespace std;

typedef pair<int, int> point;

int dj[] = {-2, -1, +1, +2, +2, +1, -1, -2};
int di[] = {-1, -2, -2, -1, +1, +2, +2, +1};

int main(){
  string s, t;
  while (cin >> s >> t){
    point start(s[0]-'a', s[1]-'1');
    point end(t[0]-'a', t[1]-'1');
    
    set<point> visited;
    queue<pair<point, int> > q;
    q.push(make_pair(start, 0));

    while (!q.empty()){
      int dist = q.front().second;
      point u = q.front().first;
      q.pop();
      if (0 <= u.first && u.first < 8 &&
	  0 <= u.second && u.second < 8 && !visited.count(u)){
	//cout << "Visiting " << u.first << " " << u.second << endl;
	if (u == end){
	  cout << "To get from "<<s<<" to "<<t<<" takes "<<dist<<" knight moves." << endl;
	  break;
	}
	visited.insert(u);
	for (int k=0; k<8; ++k){
	  q.push(make_pair(point(u.first + di[k], u.second + dj[k] ), dist + 1));
	}
      }
    }
  }
  return 0;
}
