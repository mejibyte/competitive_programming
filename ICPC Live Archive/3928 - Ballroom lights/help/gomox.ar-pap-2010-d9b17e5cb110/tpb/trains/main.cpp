#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <list>
#include <cassert>
#include <cstdlib>

using namespace std;

#define forsn(i, s, n)	for (int i = (s); i < (n); i++)
#define forn(i, n) 	forsn (i, 0, n)
#define forall(x, s)	for (typeof((s).begin()) x = (s).begin(); x != (s).end(); x++)
#define dforall(x, s)	for (typeof((s).rbegin()) x = (s).rbegin(); x != (s).rend(); x++)

typedef int Id; // station id
typedef int Time;
typedef pair<Id, Time> Nodo;

struct Edge {
	Nodo dest;
	Time cost;
};
typedef vector<Edge> Ady;
typedef map<Nodo, Ady> Grafo;

typedef map<string, pair<Id, set<Time> > > Stations;

// map<Nodo, Ady>::iterator
#define _nodo		first
#define _ady		second

// Stations::iterator
#define _info		second

// pair<Id, set<Time> >
#define _id		first
#define _timeset	second

// Nodo
#define _time		second

#define HOUR 60
#define DAY (24 * HOUR)

Id inline register_station(Stations& stations, const string& station_name, Time time) {
	Stations::iterator it(stations.find(station_name));
	if (it == stations.end()) {
		// create
		const Id a = stations.size();
		set<Time> s;
		s.insert(time);
		stations[station_name] = pair<Id, set<Time> >(a, s);
		return a;
	} else {
		pair<Id,set<Time> >& t = stations[station_name];
		t._timeset.insert(time);
		return t._id;
	}
}

inline int time_in_minutes(string& s) {
	// h:mm hh:mm hhh:mm ...
	const int l = s.size();
	assert(s[l - 3] == ':');
	return atoi(s.substr(0, l - 3).c_str()) * HOUR + atoi(s.substr(l - 2, 2).c_str());
}

void print_graph(Grafo& g) {
	forall (x, g) {
		cout << "Hasta: " << x->_nodo._id << " a las " << (x->_nodo._time / 60) << ":" << (x->_nodo._time % 60) << endl;
		forall (y, x->_ady) {
			cout << "    desde " << y->dest._id
				<< " a las " << (y->dest._time / 60) << ":" << (y->dest._time % 60)
				<< " costo: " << (y->cost / 60) << ":" << (y->cost % 60) << endl;
		}
	}
}

#define INF	0x7fffffff

inline void dijkstra(Stations& stations, Grafo& graph, const string& origen, const string& destino) {
	const Id id_origen = stations[origen]._id;
	const Id id_destino = stations[destino]._id;

	set<pair<Time, Nodo> > cola;
	map<Nodo, Time> distancia;

	// inicializar distancias
	forall (st, stations) {
		Id station_id = st->_info._id;
		forall (t, st->_info._timeset) {
			Nodo v(station_id, *t);
			if (station_id == id_destino) {
				cola.insert(pair<Time,Nodo>(0, v));
				distancia[v] = 0;
			} else {
				distancia[v] = INF;
			}
		}
	}
	while (!cola.empty()) {
		// buscar el minimo
		Time min_dist = cola.begin()->first;

		// borrarlo de la cola
		Nodo min_node = cola.begin()->second;
		cola.erase(cola.begin());

		// procesar min_node
		forall (eje, graph[min_node]) {
			const Time dist_nueva = min_dist + eje->cost;
                        const Time dist_actual = distancia[eje->dest];
			if (dist_nueva < dist_actual) {
				if (dist_actual != INF) {
					cola.erase(cola.find(pair<Time,Nodo>(dist_actual, eje->dest)));
				}
				distancia[eje->dest] = dist_nueva;
				cola.insert(pair<Time,Nodo>(dist_nueva, eje->dest));
			}
		}
	}

	list<pair<Time, Time> > salida;
	Time min_hora_llega = INF;
	forall (t, stations[origen]._timeset) {
		Nodo v(id_origen, *t);
		const Time hora_llega = *t + distancia[v] + DAY;
		min_hora_llega = min(min_hora_llega, hora_llega);
	}
	dforall (t, stations[origen]._timeset) {
		Nodo v(id_origen, *t);
		const Time hora_sale = *t;
		const Time hora_llega = *t + distancia[v];
		if (hora_llega >= min_hora_llega) continue;
		min_hora_llega = hora_llega;
		salida.push_front(pair<Time, Time>(hora_sale, distancia[v]));
	}
	forall (res, salida) {
		printf("%.2i:%.2i ", res->first / 60, res->first % 60);
		printf("%i:%.2i\n", res->second / 60, res->second % 60);
	}
}

#define add_edge(g, v1, v2, c) ((g)[(v1)].push_back((Edge){dest: (v2), cost: (c)}))
int main() {
	int ncases;
	cin >> ncases;

	forn (c, ncases) {
		Stations stations;
		Grafo graph;

		int num_trains;
		cin >> num_trains;

		// read trains and stations
		forn (t, num_trains) {
			int num_stations;
			cin >> num_stations;

			Nodo prev;
			int time = 0;
			forn (s, num_stations) {
				string time_str, station_name;
				cin >> time_str >> station_name;

				const Time cost = time_in_minutes(time_str);
				time = (time + cost) % DAY;
				const Id station_id = register_station(stations, station_name, time);

				const Nodo next(station_id, time);
				if (s != 0) {
					add_edge(graph, next, prev, cost);
				}
				prev = next;
			}
		}

		// complete the graph with the self edges for each station
		forall (station, stations) {
			const Id id = station->_info._id;
			const set<Time>& timeset = station->_info._timeset;
			if (timeset.size() == 1) continue;
			forall (t1, timeset) {
				set<Time>::iterator t2 = t1;
				t2++;
				const Nodo v1(id, *t1);
				const Nodo v2(id, t2 == timeset.end() ? *timeset.begin() : *t2);
				Time cost = v2._time - v1._time;
				if (cost < 0) cost += DAY;
				add_edge(graph, v2, v1, cost);
			}
		}

		string origen, destino;
		cin >> origen >> destino;

		dijkstra(stations, graph, origen, destino);
		if (c != ncases - 1) {
			cout << endl;
		}
	}
	return 0;
}

