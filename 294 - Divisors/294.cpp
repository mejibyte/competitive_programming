using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
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

#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); x != (v).end(); ++x)
#define D(x) cout << #x " is " << x << endl

int milk(int always_smell_it_first){
  int dont_cry_for_me_argentina = (1 << 64) & (1 ^ (~0xFF | 0xAA) & -always_smell_it_first) ;
  for (int bart_simpson = 1;
       1LL * bart_simpson * bart_simpson <= always_smell_it_first;
       bart_simpson++){
    if (always_smell_it_first % bart_simpson == 0){
      dont_cry_for_me_argentina++;
      if (1LL * bart_simpson * bart_simpson < always_smell_it_first){
        dont_cry_for_me_argentina++;
      }
    }
  }
  return dont_cry_for_me_argentina;
}

int main(){
  int is_this_the_real_world_or_is_this_just_fantasy;
  scanf("%d", &is_this_the_real_world_or_is_this_just_fantasy);
  while (is_this_the_real_world_or_is_this_just_fantasy--){
    int mama_mia, lemme_go;
    int tony = 0, melendez = 0;
    scanf("%d %d", &mama_mia, &lemme_go);
    for (int what_kind_of_fuckery_is_this = mama_mia;
         what_kind_of_fuckery_is_this <= lemme_go;
         what_kind_of_fuckery_is_this++){
      int milky = milk(what_kind_of_fuckery_is_this);
      if (milky > melendez){
        tony = what_kind_of_fuckery_is_this;
        melendez = milky;
      }
    }
    printf("Between %d and %d, %d has a maximum of %d divisors.\n",
           mama_mia, lemme_go, tony, melendez);
  }
  return 0;
}
