/* NWERC'11 solution for traindelay
 * Author: Jaap Eldering
 */

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

struct conn {
	int fr, to;
	int deptime, duration, maxdelay;
	double pdelay;
};

int orig, dest;
int nstations;
map<string,int> stations;
vector<conn> connections;

const double eps = 1E-8;

int main()
{
	int nruns;

	cout.precision(10);

	cin >> nruns;
	for(int run=1; run<=nruns; run++) {

		nstations = 0;
		stations.clear();
		connections.clear();

		string orig_str, dest_str;
		cin >> orig_str >> dest_str;

		assert( orig_str!=dest_str );

		orig = stations[orig_str] = nstations++;
		dest = stations[dest_str] = nstations++;

		int nconn;
		cin >> nconn;

		for(int i=0; i<nconn; i++) {
			string fr_str, to_str;
			conn tmp;
			int perc;

			cin >> fr_str >> to_str;

			assert( fr_str!=to_str );

			if ( stations.count(fr_str)==0 ) stations[fr_str] = nstations++;
			if ( stations.count(to_str)==0 ) stations[to_str] = nstations++;

			tmp.fr = stations[fr_str];
			tmp.to = stations[to_str];

			cin >> tmp.deptime >> tmp.duration >> perc >> tmp.maxdelay;
			tmp.pdelay = perc*0.01;

			connections.push_back(tmp);
		}

		// Declare and initialize minimal E(xpectation) of trip
		// duration per station, minute of the hour.
		vector< vector<double> > E(nstations,vector<double>(60,1E20));
		for(int m=0; m<60; m++) E[dest][m] = 0;

		// TODO: verify that this loop is executed O(#connections) times.
		int updated;
		do {
			updated = 0;

			for(size_t i=0; i<connections.size(); i++) {
				conn &c = connections[i];

				int arrtime = (c.deptime + c.duration) % 60;
				double newE = (1-c.pdelay) * (c.duration + E[c.to][arrtime]);
				for(int d=c.duration+1; d<=c.duration+c.maxdelay; d++) {
					arrtime = (c.deptime + d) % 60;
					newE += c.pdelay/c.maxdelay * (d + E[c.to][arrtime]);
				}

				for(int m=0; m<60; m++) {
					int dm = (c.deptime - m + 60) % 60;
					if ( newE+dm<E[c.fr][m]-eps && newE<1E18 ) {
//						if ( updated==0 ) {
// 							printf("updating %d -> %d @ %02d: %.3lf\n",
// 							       c.fr,c.to,m,newE+dm);
//						}
						updated = 1;
						E[c.fr][m] = newE+dm;
					}
				}
			}

		} while ( updated );

		double T = 1E20;
		for(int m=0; m<60; m++) T = min(T,E[orig][m]);

		if ( T>1E19 )
			cout << "IMPOSSIBLE\n";
		else
			cout << T << endl;
	}

	return 0;
}
