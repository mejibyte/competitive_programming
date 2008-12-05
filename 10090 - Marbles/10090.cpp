/*
  Accepted
 */
using namespace std;
#include <cstdio>
#include <climits>
#include <cassert>
#include <algorithm>

long long get_gcd(long long a, long long b, long long &x, long long &y){
  if (b > a) return get_gcd(b, a, y, x);
  if (b == 0){
    x = 1, y = 0;
    return a;
  }
  long long g, sub_x, sub_y;
  g = get_gcd(b, a%b, sub_x, sub_y);
  x = sub_y, y = sub_x - sub_y*(a/b);
  return g;
}

int main(){
  long long n, n1, n2, c1, c2;
  while (scanf("%lld", &n)==1 && n){
    scanf("%lld %lld %lld %lld", &c1, &n1, &c2, &n2);

    long long a, b, gcd;
    gcd = get_gcd(n1, n2, a, b);

    if (n % gcd != 0){
      printf("failed\n");
    }else{
      a *= (n/gcd), b *= (n/gcd);
      assert(a*n1 + b*n2 == n);


      long long lcm = n1/gcd*n2;
      long long inc_a = lcm/n1, inc_b = lcm/n2;

      if (a < 0){
        long long times = -a/inc_a;
        if (-a % inc_a) ++times;
        a += times*inc_a, b -= times*inc_b;
      }

      if (b < 0){
        long long times = -b/inc_b;
        if (-b % inc_b) ++times;
        b += times*inc_b, a -= times*inc_a;
      }



      if (a < 0 || b < 0) printf("failed\n");
      else{

        if (a > b && b >= inc_b){
          long long times = b/inc_b;
          a += times*inc_a, b -= times*inc_b;
        }

        else if (b > a && a >= inc_a){
          long long times = a/inc_a;
          a -= times*inc_a, b += times*inc_b;
        }


        pair<long long, long long> ans;
        long long best = LLONG_MAX;

        //Listo, tenemos una posible solución.
        if (a*c1 + b*c2 < best){
          best = a*c1 + b*c2;
          ans = make_pair(a, b);
        }

        //Ahora bajemos esto al otro extremo
        if (a > b){
          //Bajemos a
          long long times = a/inc_a;
          a -= times*inc_a, b += times*inc_b;

          if (a*c1 + b*c2 < best){
            best = a*c1 + b*c2;
            ans = make_pair(a, b);
          }

        }else{
          //Bajemos b
          long long times = b/inc_b;
          a += times*inc_a, b -= times*inc_b;
          if (a*c1 + b*c2 < best){
            best = a*c1 + b*c2;
            ans = make_pair(a, b);
          }
        }


        printf("%lld %lld\n", ans.first, ans.second);
      }

    }
  }
  return 0;
}
