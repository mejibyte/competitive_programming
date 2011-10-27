/*
  Accepted
 */
#include <stdio.h>
#include <assert.h>
#include <math.h>

#define MAXN 10001
#define EPS 1e-9

struct point{
  double x, y;
};

point p[MAXN];

int main(){
  int T, n, w;
  double capacity, initial, out, in;
  scanf("%d", &T);
  while (T--){
    scanf("%d", &n);
    for (int i=0; i<n; ++i){
      double x, y;
      scanf("%lf %lf", &x, &y);
      p[i].x = x; p[i].y = y;
    }
    scanf("%d", &w);

    capacity = 0.0;
    for (int i=0; i<n; ++i){
      int j = (i+1)%n;
      capacity += p[i].x*p[j].y - p[j].x*p[i].y;
    }
    capacity *= (double)w / 2;

    assert(capacity > 0.0);

    scanf("%lf %lf %lf", &initial, &out, &in);
    
    initial = (capacity * initial) / 100.0; //Convert from percentage to volume

    /*
    printf("Capacity es: %lf\n", capacity);
    printf("Initial es: %lf\n", initial);  
    */

    initial -= out;
    if (initial < 0.0 - EPS){
      printf("Lack of water. ");
      initial = 0.0;
    }

    initial += in;
    if (initial > capacity + EPS){
      printf("Excess of water. ");
      initial = capacity;
    }

    initial = (initial * 100.0) / capacity; //Convert from volume to percentage

    int answer = initial;
    printf("Final percentage: %d\%\n", answer);
  }
  return 0;
}
