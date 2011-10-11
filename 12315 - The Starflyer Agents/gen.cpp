using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <fstream>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <deque>
#include <stack>
#include <list>
#include <map>
#include <set>

#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << x << endl

int main(){
    int Casos = 1000;
    for (int c = 0; c < Casos; ++c) {
        printf("random%d 3\n", c);
        for (int i = 0; i < 3; ++i){
            printf("a(");
            for (int j = 0; j < 6; ++j) {
                if (rand() % 100 < 50) { // function
                    printf("b(%c)", rand() % 6 + 'A');
                } else {
                    printf("%c", rand() % 6 + 'A');
                }
                if (j + 1 < 6) printf(",");
            }
            printf(")\n");
        }
    }
    return 0;
}