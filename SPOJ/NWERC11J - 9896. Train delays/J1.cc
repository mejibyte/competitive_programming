/*
 *   [NWERC'11] Train delay
 *   by: Jan Kuipers
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <map>

using namespace std;

const double infty = 1e100;
const double eps = 1e-10;

int N;
map<string,int> city_ids;

int city_id (string s) {
  if (!city_ids.count(s))
    city_ids[s] = N++;
  return city_ids[s];
}

int main () {

  int runs;
  cin>>runs;

  while (runs--) {

    N=0;
    city_ids.clear();

    string s;
    cin>>s; int start = city_id(s);
    cin>>s; int finish = city_id(s);

    int M;
    cin>>M;

    vector<int> fr(M),to(M),t(M),dt(M),p(M),d(M);

    for (int i=0; i<M; i++) {
      cin>>s; fr[i] = city_id(s);
      cin>>s; to[i] = city_id(s);
      cin>>t[i]>>dt[i]>>p[i]>>d[i];
    }

    vector<vector<double> > best(N, vector<double>(60,infty));
    for (int i=0; i<60; i++)
      best[finish][i] = 0;

		for (bool changed=true; changed;) {
			changed=false;
				
      for (int i=0; i<M; i++) {
				double time = (1-p[i]/100.0) * (dt[i] + best[to[i]][(t[i]+dt[i])%60]);
				for (int j=1; j<=d[i]; j++)
					time += p[i]/100.0/d[i] * (dt[i] + j + best[to[i]][(t[i]+dt[i]+j)%60]);
				
				if (time < eps*infty && time < best[fr[i]][t[i]]-eps) {
					best[fr[i]][t[i]] = time;
					changed = true;
					
					for (int j=0; j<60; j++) 
						if (best[fr[i]][t[i]]+(60+t[i]-j)%60 < best[fr[i]][j]-eps)
							best[fr[i]][j] = best[fr[i]][t[i]]+(60+t[i]-j)%60;
				}
      }
    }

    double res = infty;
    for (int i=0; i<60; i++)
      res = min(res,best[start][i]);

    if (res == infty)
      cout << "IMPOSSIBLE" << endl;
    else      
      cout << setprecision(10) << res << endl;		
  }

  return 0;
}
