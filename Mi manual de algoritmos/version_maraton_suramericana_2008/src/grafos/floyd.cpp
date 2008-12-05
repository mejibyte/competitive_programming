/*
  g[i][j] = Distancia entre el nodo i y el j.
 */
unsigned long long g[101][101];

void floyd(){
  //Llenar g
  //...

  for (int k=0; k<n; ++k){
    for (int i=0; i<n; ++i){
      for (int j=0; j<n; ++j){
	g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
      }
    }
  }
  /*
    Acá se cumple que g[i][j] = Longitud de la ruta más corta de i a j.
   */
}
