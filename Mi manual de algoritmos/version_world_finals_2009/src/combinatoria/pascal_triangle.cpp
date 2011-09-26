const int N = 30;
long long choose[N+1][N+1];
  /* Binomial coefficients */
  for (int i=0; i<=N; ++i) choose[i][0] = choose[i][i] = 1;
  for (int i=1; i<=N; ++i)
    for (int j=1; j<i; ++j)
      choose[i][j] = choose[i-1][j-1] + choose[i-1][j];
