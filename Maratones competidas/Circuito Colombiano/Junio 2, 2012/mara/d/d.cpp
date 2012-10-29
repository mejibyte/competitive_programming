using namespace std;

#include <algorithm>
#include <iostream>
#include <iterator>
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
#include <map>
#include <set>

# define foreach (x, v) for (typeof (v).begin() x = (v).begin(); x != (v).end(); ++x)
# define D(x) cout << #x " = " << (x) << endl
# define For(i, a,  b) for (int i = (a); i < (b); i++)

typedef pair<double, double> pdd;

const double pi = M_PI;

vector<double> points;




void solve(double range){
	int n = points.size();
	int best_n = 0;
	double best_ang = 0.0;
	for (double ang = 0.0; ang < 360.0 ; ang += 0.1){
		double left = ang - range / 2;
		double right = ang + range / 2;
		if (left < 0){
			left += 360;
		}else if (right > 360){
			right -= 360;
		}	
		vector <double>::iterator l, r;
		
		l = upper_bound(points.begin(),points.end(),left);
		r = lower_bound(points.begin(),points.end(),right);
				
		int total;
		
		
		
		if (right < left) {
			total = points.end() - l + r - points.begin();	
		}
		else {
			total = r - l;	
		}
		if (total > best_n){
			best_n = total;
			best_ang = ang;
		}

	}
	printf("Point the camera at angle %.1lf to view %d infested trees.\n",best_ang,best_n);
}

double convert (double ang){
	ang = fmod(pi / 2 - ang + 2 * pi, 2*pi);
	ang = ang*180/pi;
	return ang;
}


int main(){
	
	
	int n;
	while (cin >> n){
		if (n == 0) break;
		points.clear();
		
		double x_cam, y_cam, ang_s;
		cin >> x_cam >> y_cam >> ang_s;
		
		for (int i = 0; i < n; i++){
			double x, y;
			cin >> x >> y;
			double ang = fmod(atan2(y-y_cam, x-x_cam) + 2 * pi, 2*pi);
			points.push_back(convert(ang));
			//D(convert(ang));
		}
		sort(points.begin(), points.end());
		
		
		solve(ang_s);
		
	
	}
	return 0;
}


