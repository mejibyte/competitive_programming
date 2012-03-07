/*
 *   [NWERC'11] Train delay
 *   by: Jan Kuipers
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <string>
#include <map>

using namespace std;

const double infty = 1e100;
const double eps = 1e-10;

struct train { int fr, ti, dt, pr, de; };

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
		cin>>s;	int fr = city_id(s);
		cin>>s;	int to = city_id(s);

		vector<vector<train> > conn;

		int M;
		cin>>M;
		for (int i=0; i<M; i++) {
			int fr,to,ti,dt,pr,de;
			cin>>s;	fr = city_id(s);
			cin>>s;	to = city_id(s);
			cin>>ti>>dt>>pr>>de;
			conn.resize(N);
			conn[to].push_back((train) {fr,ti,dt,pr,de});
		}

		priority_queue<pair<double,int> > pq;
		vector<vector<double> > best(N, vector<double>(60, infty));
		
		pq.push(make_pair(0,60*to));
		for (int t=0; t<60; t++) 
			best[to][t] = 0;

		while (!pq.empty()) {
			int to = pq.top().second / 60;
			int ti = pq.top().second % 60;
			double time = -pq.top().first;
			pq.pop();
			if (time > best[to][ti]+eps) continue;

			for (int i=0; i<conn[to].size(); i++) {
				train x = conn[to][i];
				double newbest = (1-x.pr/100.0) * (x.dt + best[to][(x.ti+x.dt)%60]);
				for (int de=1; de<=x.de; de++)
					newbest += x.pr/100.0/x.de * (de + x.dt + best[to][(x.ti+x.dt+de)%60]);

				if (best[x.fr][x.ti] > newbest+eps) {
					pq.push(make_pair(-newbest,60*x.fr+x.ti));
					for (int t=0; t<60; t++) 
						if (best[x.fr][(x.ti-t+60)%60] > newbest + t + eps) 
							best[x.fr][(x.ti-t+60)%60] = newbest + t;
				}
			}
		}

		double res = infty;
    for (int t=0; t<60; t++)
      res = min(res,best[fr][t]);

    if (res == infty)
      cout << "IMPOSSIBLE" << endl;
    else
      cout << setprecision(10) << res << endl;
  }

	return 0;
}
