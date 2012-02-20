/*
  O(n^3)

 dp[i][j] = Mínimo costo de partir la cadena entre las particiones i e j, ambas incluídas.
 */
int dp[1005][1005];
int p[1005];

int cubic(){
  int n, m;
  while (scanf("%d %d", &n, &m)==2){
    p[0] = 0;
    for (int i=1; i<=m; ++i){
      scanf("%d", &p[i]);
    }
    p[m+1] = n;
    m += 2;

    for (int i=0; i<m; ++i){
      dp[i][i+1] = 0;
    }
    
    for (int i=m-2; i>=0; --i){
      for (int j=i+2; j<m; ++j){
	dp[i][j] = p[j]-p[i];
	int t = INT_MAX;
	for (int k=i+1; k<j; ++k){
	  t = min(t, dp[i][k] + dp[k][j]);
	}
	dp[i][j] += t;
      }
    }

    printf("%d\n", dp[0][m-1]);
  }
  return 0;
}


/*
  O(n^2)

  dp[i][j] = Mínimo costo de partir la cadena entre las particiones i e j, ambas incluídas.
  pivot[i][j] = Índice de la partición que usé para lograr dp[i][j].
 */
int dp[1005][1005], pivot[1005][1005];
int p[1005];

int quadratic(){
  int n, m;
  while (scanf("%d %d", &n, &m)==2){
    p[0] = 0;
    for (int i=1; i<=m; ++i){
      scanf("%d", &p[i]);
    }
    p[m+1] = n;
    m += 2;

    for (int i=0; i<m-1; ++i){
      dp[i][i+1] = 0;
    }
    for (int i=0; i<m-2; ++i){
      dp[i][i+2] = p[i+2] - p[i];
      pivot[i][i+2] = i+1;
    }
    
    for (int d=3; d<m; ++d){ //d = longitud
      for (int j, i=0; (j = i + d) < m; ++i){
	dp[i][j] = p[j] - p[i];
	int t = INT_MAX, s;
	for (int k=pivot[i][j-1]; k<=pivot[i+1][j]; ++k){
	  int x = dp[i][k] + dp[k][j];
	  if (x < t) t = x, s = k;
	}
	dp[i][j] += t, pivot[i][j] = s;
      }
    }

    printf("%d\n", dp[0][m-1]);
  }
  return 0;
}
