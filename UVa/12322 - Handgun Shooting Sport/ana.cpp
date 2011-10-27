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
 
bool shot [1000];
vector < pair <long double, long double> > angles;

void shoot(const long double &begin, const long double &end, const int &index){
	shot[index] = true;
	if (index < angles.size() - 1){
		long double begin_next = angles[index + 1].first;
		if (begin_next >= begin and begin_next <= end) 
				shoot(begin_next, min(end, angles[index + 1].second) , index + 1);
	}
	
}

int main(){
	int B;
	while(cin >> B){
		if (B == 0) break;
		// Read billboards
		angles.clear();
		for (int i = 0; i < B; i++){
			int x1, x2, y1, y2;
			cin >> x1 >> y1 >> x2 >> y2;
			//Convert to polar coordinates
			long double angle1 = atan2((long double) y1, (long double) x1);
			long double angle2 = atan2((long double) y2, (long double) x2);
			angles.push_back(make_pair(min(angle1, angle2), max(angle1,angle2) )); 
		}
		sort(angles.begin(), angles.end());
		
		/*for (int i = 0; i < B; i++){
			cout << angles[i].first << "  " << angles[i].second << endl;
		}*/
		
		for (int i = 0; i < B; i++) shot[i] = false;
		int shots = 0;
		for (int i = 0; i < B; i++){
			if (!shot[i]){
				//printf("Shot billboard number %d\n", i);
				shots++;
				shoot(angles[i].first, angles[i].second, i);
			}
		}		
		cout << shots << endl;
	}
    return 0;
}