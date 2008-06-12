#include <iostream>
#include <queue>
#include <vector>
#include <sstream>


using namespace std;

inline string intToStr(const int &n){stringstream ss; ss<<n; string s; ss>>s; return s; }
inline int strToInt(const string &n){stringstream ss; ss<<n; int s; ss>>s; return s; }

int main(){
  int cases;
  cin >> cases;
  while (cases--){
    vector<bool> forbidden(10000, false);
    vector<bool> visited(10000, false);
    

    int start = 0;
    for (int i=0; i<4; ++i){
      int x; scanf("%d", &x);
      start = (start * 10) + x;
    }

    int end = 0;
    for (int i=0; i<4; ++i){
      int x; scanf("%d", &x);
      end = (end * 10) + x;
    }
    
    int n;
    cin >> n;
    while (n--){
      int f=0;
      for (int i=0; i<4; ++i){
	int x; scanf("%d", &x);
	f = (f * 10) + x;
      }
      forbidden[f] = true;
    }

    queue<pair<int, int> > q;
    int answer = -1;
    q.push(make_pair(start, 0));
    while (!q.empty()){
      int node = q.front().first;
      int dist = q.front().second;
      q.pop();
      if (node == end){
	answer = dist;
	break;
      }
      if (visited[node]){
	continue;
      }
      visited[node] = true;
      for (int i=0; i<4; ++i){
	stringstream ss;
	ss << node;
	string s;
	ss >> s;      
	string t;
	char digit;
	int neighbour;

	t = s;
	digit = s[i];
	digit = '0' + ((digit - '0' + 1) % 10);
	t[i] = digit;
	//cout << "t es: " << t << endl;
	//cout << "neighbour es: " << strToInt(t) << endl;
	neighbour = strToInt(t);
	if (!forbidden[neighbour]){
	  q.push(make_pair(neighbour, dist + 1));
	  //cout << "Empuje " << q.front().first << endl;
	}

	t = s;
	digit = s[i];
	digit = '0' + ((digit - '0' + 9) % 10);
	t[i] = digit;
	neighbour = strToInt(t);
	//cout << "neighbour es: " << strToInt(t) << endl;
      	if (!forbidden[neighbour]){
	  q.push(make_pair(neighbour, dist + 1));
	  //cout << "Empuje " << q.front().first << endl;
	}
      }
    }
    cout << answer << endl;
    
  }
  return 0;
}
