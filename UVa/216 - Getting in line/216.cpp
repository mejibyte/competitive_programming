/*
  Accepted
 */
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(){
  int n, N=1;
  while (cin >> n && n){
    
    vector<pair<int, int> > v(n);
    for (int i=0; i<n; ++i){
      cin >> v[i].first >> v[i].second;
    }
    vector<pair<int, int> > solution;
    double best = 1E100;

    sort(v.begin(), v.end());
    do{
      double t = 0.0;
      for (int i=0; i<n-1; ++i){
	t += hypot(v[i].first-v[i+1].first, v[i].second-v[i+1].second) + 16.0;
      }
      if (t < best){
	solution = v;
	best = t;
      }
    }while(next_permutation(v.begin(), v.end()));

    printf("**********************************************************\n");
    printf("Network #%d\n", N++);
    for (int i=0; i<n-1; ++i){
      printf("Cable requirement to connect (%d,%d) to (%d,%d) is %.2f feet.\n",
	     solution[i].first, solution[i].second,
	     solution[i+1].first, solution[i+1].second,
	     hypot(solution[i].first - solution[i+1].first,
		   solution[i].second - solution[i+1].second) + 16.0);
    }
    printf("Number of feet of cable required is %.2f.\n", best);
  }
  return 0;
}
