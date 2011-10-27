/*
  Backtracking. Infinitely slow.
 */
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
  for (int i=0; i<6; ++i) times[t[i]]++;
  switch(c){
  case ones:
    return times[1] * 1;
  case twos:
    return times[2] * 2;
  case threes:
    return times[3] * 3;
  case fours:
    return times[4] * 4;
  case fives:
    return times[5] * 5;
  case sixes:
    return times[6] * 6;
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

int bonus;
int best_score;
int best_match[13]; //best_match[i] = Turn matched with category i
int current_match[13];

void backtrack(int i, int used_categories, int current_score){
  if (i == 13){
    int sum = 0;
    for (int c=ones; c<=sixes; ++c) sum += score(turns[best_match[c]], c);
    int current_bonus = 0;
    if (sum >= 63){
      current_score += (current_bonus = 35); //bonus
    }
    printf("Found a matching of %d:\n", current_score);
    for (int c=ones; c<=full_house; ++c){
      printf("%d ", current_match[c]);
    }
    printf("\n");

    if (current_score > best_score){
      best_score = current_score;
      bonus = current_bonus;
      memcpy(best_match, current_match, sizeof best_match);
    }
    return;
  }

  for (int c=ones; c<=full_house; ++c){
    if (!(used_categories & (1 << c))){
      current_match[c] = i;
      backtrack(i + 1, used_categories | (1 << c), current_score + score(turns[i], c));
      current_match[c] = -1;
    }
  }
}


int main(){
  while (true){
    for (int i=0; i<13; ++i){
      for (int j=0; j<5; ++j){
        if (scanf("%d", &turns[i][j]) != 1) return 0;
      }
    }

    best_score = 0;
    backtrack(0, 0, 0);

    for (int c=ones; c<=full_house; ++c){
      printf("%d ", best_match[c]);
      printf("%d %d\n", bonus, best_score);
    }

  }
  return 0;
}
