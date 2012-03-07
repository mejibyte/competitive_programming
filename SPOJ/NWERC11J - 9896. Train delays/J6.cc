// @EXPECTED-RESULTS@: TIMELIMIT

#include <iostream>
#include <cstdio>
#include <string>
#include <map>
#include <vector>
#include <float.h>
#include <algorithm>

using namespace std;

#define MAX 2005
#define INF (DBL_MAX*.25)

struct edge {
	int from, to, delay, probDelay, depart, time;
};

map<string,int> stringToID;
vector<edge> in[MAX];
string cities[MAX];
int numCities;
double cost[MAX][60];
bool changed[MAX][60];

int getID(string s) {
	if (stringToID.find(s) == stringToID.end()) {
		for (int i = 0; i < 60; i++) {
			cost[numCities][i] = INF;
			changed[numCities][i] = false;
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

		for (int i = 0; i < 60; i++) {
			cost[target][i] = 0;
			changed[target][i] = true;
		}

		do {
			int bestMinute, bestLoc;
			double bestCost = INF;
			for (int i = 0; i < numCities; i++) {
				for (int j = 0; j < 60; j++) {
					if (changed[i][j] && cost[i][j] < bestCost) {
						bestCost = cost[i][j];
						bestLoc = i;
						bestMinute = j;
					}
				}
			}
			if (bestCost == INF) {
				break;
			}
			changed[bestLoc][bestMinute] = false;
			// "wait"
			for (int i = 1; i < 60; i++) {
				int newMinute = (60 + bestMinute - i) % 60;
				if (cost[bestLoc][bestMinute] + i < cost[bestLoc][newMinute]) {
					cost[bestLoc][newMinute] = cost[bestLoc][bestMinute] + i;
					changed[bestLoc][newMinute] = true;
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
				if (newCost < cost[in[bestLoc][i].from][in[bestLoc][i].depart]) {
					cost[in[bestLoc][i].from][in[bestLoc][i].depart] = newCost;
					changed[in[bestLoc][i].from][in[bestLoc][i].depart] = true;
				}
			}
		} while (true);

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
