// Train Delay
// Solution by Thomas Beuman

// Algorithm: Dijkstra (w/o heap) with revisits
// Time complexity: O(d * n^2 * #revisits)
// Result: Correct or Timelimit?

#include <cstdio>
#include <string>
using namespace std;

typedef double dbl; // Optional: long double for more precision

const int N = 1000;

string Name[2*N]; // Station names
int Origin[N], Dest[N], M[N], T[N], P[N], D[N];
dbl ETA[2*N][60]; // Expected time of arrival per station-time combo
dbl Processed[N]; // Last ETA processed per train

// Add new station and initialize ETA
void addstation (char name[], int& S)
{ Name[S] = name;
  for (int m = 0; m < 60; m++)
    ETA[S][m] = 1e9;
  S++;
}

// Return index of station
int station_index (char station[], int& S)
{ int i;
  for (i = 0; i < S && Name[i] != station; i++); // Find index
  if (i == S) // Not found
    addstation(station, S);
  return i;
}    

int main()
{ int runs, run, n, S, i, j, k=0, m, s1, s2, s;
  dbl t, mintime;
  char station1[21], station2[21];
  scanf("%d\n", &runs);
  for (run = 0; run < runs; run++)
  { scanf("%s %s\n", station1, station2);
    S = 0;
    addstation(station1, S);
    addstation(station2, S);
    scanf("%d\n", &n);
    for (i = 0; i < n; i++)
    { scanf("%s %s %d %d %d %d\n", station1, station2, &M[i], &T[i], &P[i], &D[i]);
      Origin[i] = s1 = station_index(station1, S);
      Dest[i] = s2 = station_index(station2, S);
      Processed[i] = 1e9;
      // Set ETA for trains to final destination (= 1)
      if (s2 == 1)
        ETA[s1][M[i]] = min(ETA[s1][M[i]], (dbl)(T[i] + P[i]/100.0 * (D[i]+1)/2.0));
    }
    // Dijkstra(-ish) (nodes may get revisited)
    while (true)
    { // Look for train with smallest unprocessed ETA
      mintime = 1e9;
      for (i = 0; i < n; i++)
        if ((t = ETA[Origin[i]][M[i]]) < Processed[i] && t < mintime)
        { mintime = t;
          k = i;
        }
      if (mintime == 1e9) // Nothing left to process
        break;
      Processed[k] = mintime;
      s = Origin[k];
      // Update ETA for all times at station s
      for (m = 0; m < 60; m++)
        ETA[s][m] = min(ETA[s][m], (60+M[k]-m)%60 + mintime);
      // Update ETA for all trains to station s
      for (i = 0; i < n; i++)
        if (Dest[i] == s)
        { t = 0;
          for (j = 0; j <= D[i]; j++)
            t += (j == 0 ? 1 - P[i]/100.0 : P[i]/100.0/D[i]) * (T[i]+j + ETA[s][(M[i]+T[i]+j)%60]);
          ETA[Origin[i]][M[i]] = min(ETA[Origin[i]][M[i]], t);
        }
    }
    // Look for best departure time at the station of departure
    mintime = 1e9;
    for (m = 0; m < 60; m++)
      mintime = min(mintime, ETA[0][m]);
    if (mintime < 1e9)
      printf("%.10lf\n", (double)mintime);
    else
      printf("IMPOSSIBLE\n");
  }
  return 0;
}
