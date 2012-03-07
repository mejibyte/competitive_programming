// @EXPECTED_RESULTS@: CORRECT

#include <iostream>
#include <cstdio>
#include <string>
#include <map>
#include <vector>
#include <float.h>
#include <algorithm>
#include <queue>

using namespace std;

#define MAX 2005
#define INF (DBL_MAX*.25)
#define EPS 1e-8
#define PUSH(a,b) pq.push(make_pair(cost[a][b], make_pair(a,b)))

struct edge {
	int from, to, delay, probDelay, depart, time;
};

map<string,int> stringToID;
vector<edge> in[MAX];
string cities[MAX];
int numCities;
double cost[MAX][60];
typedef pair<double,pair<int,int> > pdpii;

int getID(string s) {
	if (stringToID.find(s) == stringToID.end()) {
		for (int i = 0; i < 60; i++) {
			cost[numCities][i] = INF;
			in[numCities].clear();
		}
		cities[numCities] = s;
		stringToID[s] = numCities;
		numCities++;
	}
	return stringToID[s];
}

int main(int argc, char**argv) {
	int numCases;
	cin >> numCases;

	while (numCases --> 0) {
		stringToID.clear();
		numCities = 0;

		string startS, targetS;
		cin >> startS >> targetS;

		int start = getID(startS);
		int target = getID(targetS);

		int numConnections;
		cin >> numConnections;
		for (int i = 0; i < numConnections; i++) {
			string fromS, toS;
			edge e;
			cin >> fromS >> toS >> e.depart >> e.time >> e.probDelay >> e.delay;
			e.from = getID(fromS);
			e.to = getID(toS);
			in[e.to].push_back(e);
		}

		priority_queue<pdpii, vector<pdpii>, greater<pdpii> > pq;
		for (int i = 0; i < 60; i++) {
			cost[target][i] = 0.;
			PUSH(target,i);
		}
		while (!pq.empty()) {
			pair<double,pair<int,int> > best = pq.top();
			pq.pop();

			int bestLoc = best.second.first;
			int bestMinute = best.second.second;

			// "wait"
			for (int i = 1; i < 60; i++) {
				int newMinute = (60 + bestMinute - i) % 60;
				if (cost[bestLoc][bestMinute] + i + EPS < cost[bestLoc][newMinute]) {
					cost[bestLoc][newMinute] = cost[bestLoc][bestMinute] + i;
					PUSH(bestLoc,newMinute);
				}
			}
			// take a (possibly delayed) train
			for (int i = 0; i < (signed) in[bestLoc].size(); i++) {
				int arriv = (in[bestLoc][i].depart + in[bestLoc][i].time) % 60;
				// punctual train
				double newCost = (cost[bestLoc][arriv] + in[bestLoc][i].time) * (1. - in[bestLoc][i].probDelay / 100.);

				// delayed train
				double delayCost = 0.;
				for (int j = 1; j <= in[bestLoc][i].delay; j++) {
					delayCost += ((cost[bestLoc][(arriv + j) % 60] + j + in[bestLoc][i].time) * in[bestLoc][i].probDelay / (100. * in[bestLoc][i].delay));
				}

				newCost += delayCost;
				if (newCost + EPS < cost[in[bestLoc][i].from][in[bestLoc][i].depart]) {
					cost[in[bestLoc][i].from][in[bestLoc][i].depart] = newCost;
					PUSH(in[bestLoc][i].from,in[bestLoc][i].depart);
				}
			}
		};

		double mini = INF;
		for (int i = 0; i < 60; i++) {
			mini = min(mini, cost[start][i]);
		}
		if (mini < INF) {
			printf("%12.12lf\n", mini);
		} else {
			cout << "IMPOSSIBLE" << endl;
		}
	}
}
