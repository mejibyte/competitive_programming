#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool g[200][200]; //matriz de adyacencia del grafo
bool bicolorable;

bool visiteEdge(const int &u, const int &v, vector<int> visitas){
  for (int i=0; i<visitas.size()-1; i++){
    if ((visitas[i] == u && visitas[i+1] == v ) || (visitas[i] == v && visitas[i+1] == u))
      return true;
  }
  return false;
}

void bt(int nodo, const int &n, vector<int> visitados){
  if (!bicolorable) return;
  vector<int> vecinos;
  //find neighbours
  for (int i=0; i<n; ++i){
    if (g[nodo][i]) vecinos.push_back(i);
  }
  //backtrack for each neighbour
  for (int i=0; i<vecinos.size(); ++i){
    if (!visiteEdge(nodo, vecinos[i], visitados)){
      int k = -1;
      for (int j=0; j<visitados.size(); ++j){
	if (visitados[j] == vecinos[i]) k = j;	
      }
      if (k > -1 && ((visitados.size() - k) % 2) == 1){
	/*it means I have already visited node vecinos[i], which is at position k
	  of visitados, i.e, vecinos[i] = visitados[k]. It also means that I traveled
	  an odd number of nodes to arrive to vecinos[i] again, which means the graph
	  has an odd cycle and  thus is not bicolorable. */
	bicolorable = false;
      }
      vector<int> temp(visitados);
      temp.push_back(vecinos[i]);
      e[nodo][vecinos[i]] = e[vecinos[i]][nodo] = true;
      bt(vecinos[i], n, temp);      
    }
  }
  
}

int main(){
  int n;
  cin >> n;
  while (n){
    //process case
    memset(g, 0, sizeof(g));
    bicolorable = true;
    int l;
    cin >> l;
    //read graph
    for (int i=0; i<l; ++i){
      int x, y;
      cin >> x >> y;
      g[x][y] = g[y][x] = true;
    }

    for (int i=0; i<n; ++i){
      //bt starting at every node
      if (bicolorable){
	vector<int> visitados;
	visitados.push_back(i);
	bt(i, n, visitados);
      }
    }
    if (!bicolorable) cout << "NOT BICOLORABLE.\n";
    else cout << "BICOLORABLE.\n";
    cin >> n;
  }
  return 0;
}
