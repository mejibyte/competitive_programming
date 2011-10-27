using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <fstream>
#include <numeric>
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
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << x << endl

typedef int turn[5];

enum category {
  ones, twos, threes, fours, fives, sixes, chance, three_of_a_kind,
  four_of_a_kind, five_of_a_kind, short_straight, long_straight,
  full_house
};

int score(turn t, int c){
  int times[7] = {0};
  for (int i=0; i<5; ++i) times[t[i]]++;
  switch(c){
  case ones:
  case twos:
  case threes:
  case fours:
  case fives:
  case sixes:
    return times[c+1] * (c+1);
  case chance:
    return accumulate(t, t+5, 0);
  case three_of_a_kind:
    for (int i=1; i<=6; ++i) if (times[i] >= 3) return accumulate(t, t+5, 0);
    return 0;
  case four_of_a_kind:
    for (int i=1; i<=6; ++i) if (times[i] >= 4) return accumulate(t, t+5, 0);
    return 0;
  case five_of_a_kind:
    for (int i=1; i<=6; ++i) if (times[i] >= 5) return 50;
    return 0;
  case short_straight:
    for (int i=1; i<=3; ++i)
      if (times[i] > 0  && times[i+1] > 0 && times[i+2] > 0 && times[i+3] > 0) return 25;
    return 0;
  case long_straight:
    for (int i=1; i<=2; ++i)
      if (times[i] > 0  && times[i+1] > 0 && times[i+2] > 0 && times[i+3] > 0 && times[i+4] > 0) return 35;
    return 0;

  case full_house:
    for (int i=1; i<=6; ++i)
      for (int j=1; j<=6; ++j)
        if (times[i] == 3 && times[j] == 2) return 40;
    return 0;
  default:
    printf("Something very bad happened.\n");
  }
  return 0;
}

turn turns[13];

int dp[13][1 << 13];
/*
  dp[i][mask] = Best score having matched categories [0..i] and turns <on> on mask.
 */
int choice[13][1 << 13];

int main(){
  while (true){
    for (int i=0; i<13; ++i){
      for (int j=0; j<5; ++j){
        if (scanf("%d", &turns[i][j]) != 1) return 0;
      }
    }

    for (int i=0; i<13; ++i)
      for (int j=0; j<(1 << 13); ++j)
        dp[i][j] = INT_MIN, choice[i][j] = -1;


    //First category
    for (int t=0; t<13; ++t){
      dp[ones][1 << t] = score(turns[t], ones);
      choice[ones][1 << t] = t;
    }
    //Let's dance!
    for (int c=twos; c<=full_house; ++c){
      for (int mask = 0; mask < (1 << 13); ++mask){
        if (__builtin_popcount(mask) != c + 1) continue;
        for (int t=0; t<13; ++t){
          int prev_mask = mask & ~(1 << t);

          int canDo = dp[c-1][prev_mask] + score(turns[t], c);
          if (canDo > dp[c][mask]){
            dp[c][mask] = canDo;
            choice[c][mask] = t;
          }
        }
        if (c == sixes && dp[c][mask] >= 63){
          //Add bonus
          dp[c][mask] += 35;
        }
      }
    }

    //Now find the matching from the computed table
    //The last state is dp[all_categories][all_turns] = dp[12][11111...1111B]
    int match[13];
    for (int c=12, mask = (1 << 13) - 1; c >= 0; c--){
      match[c] = choice[c][mask];
      mask &= ~(1 << choice[c][mask]);
    }
    int sum = 0, bonus = 0;
    for (int c = ones; c <= full_house; ++c){
      int s = score(turns[match[c]], c);
      printf("%d ", s);
      sum += s;
      if (c == sixes && sum >= 63){
        sum += (bonus = 35);
      }

    }
    //assert(sum == dp[12][(1 << 13) - 1]);
    printf("%d %d\n", bonus, sum);
  }
  return 0;
}
