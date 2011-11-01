// Stolen from: http://tausiq.wordpress.com/2011/06/17/uva-10298-power-strings/

// http://uva.onlinejudge.org/external/102/10298.html
// Runtime: 0.808s
// Tag: Adhoc 

// @BEGIN_OF_SOURCE_CODE

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <cctype>
#include <stack>
#include <queue>
#include <list>
#include <vector>
#include <map>
#include <sstream>
#include <cmath>
#include <bitset>
#include <utility>
#include <set>
#include <numeric>

#define INF_MAX 2147483647
#define INF_MIN -2147483647
#define pi acos(-1.0)
#define N 1000005
#define LL long long

#define For(i, a, b) for( int i = (a); i < (b); i++ )
#define Fors(i, sz) for( size_t i = 0; i < sz.size (); i++ )
#define Fore(it, x) for(typeof (x.begin()) it = x.begin(); it != x.end (); it++)
#define Set(a, s) memset(a, s, sizeof (a))
#define Read(r) freopen(r, "r", stdin)
#define Write(w) freopen(w, "w", stdout)

int dr [] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dc [] = {0, 1, 1, 1, 0, -1, -1, -1};

using namespace std;

char ch [N + 10];

int main ()
{
    while ( scanf ("%s", ch) ) {
        if ( strcmp (ch, ".") == 0 ) break;

        int len = strlen (ch);
        int power = 1;

        for ( int i = 2; i <= len; i++ ) {
            if ( len % i == 0 ) {
                int L = len / i;
                bool flag = true;
                for ( int j = L; j < len; j++ ) {
                    if ( ch [j] != ch [j % L] ) { flag = false; break; }
                }

                if ( flag ) { power = max (power, i); }
            }
        }

        printf ("%d\n", power);
    }

	return 0;
}

// @END_OF_SOURCE_CODE
