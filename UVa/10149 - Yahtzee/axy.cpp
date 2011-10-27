/*
we can use 13 bits to record which category is used,
one category is used is represented by setting a bit as follows,

for (int combi = 0, add = 1 << c; combi < ncombinations; ++combi) {

Here, combi represents the bit combination, and add is the new added category.

Secondly, we can use DP to find the best categorization
for each upper score (upper score refers to the sum score of the first
six categories).
We need to record each of the 64 ([0, 63]) upper score conditions, and
if a new higher score with the same upper score could be achieved by
a new categorization, we could adjust the old categorization
for this new one as follows,

int newscore = score + dp[combi][u];
int newupper = upper + u < nupper ? upper + u : nupper - 1;
if (newscore > dp[combi|add][newupper]) {
 dp[combi|add][newupper] = newscore;
 previous[combi|add][newupper].combi = combi;
 previous[combi|add][newupper].upper = u;
}

Here, previous is used to restore the categorization.

At last, we check for the best score within the upper scores
of full categorization, and give a bonus for the upper score of 63 as folllows,

 int combi = ncombinations - 1;
 int upper = nupper - 1;
 bonus = 35;
 score = dp[combi][upper] + bonus;
 for (int u = 0; u < nupper; ++u) {
   if (score < dp[combi][u]) {
     bonus = 0;
     score = dp[combi][u];
     upper = u;
   }
 }
*/
/*
   Sebastian Arcila Valenzuela
   sebastianarcila@gmail.com
   2009
   @(#)TEMPLATE.c.tpl
 */

/*#include <config.h>
#include "10149.h"
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <assert.h>
#include <stdarg.h>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <deque>
#include <list>
#include <queue>
#include <stack>
#include <set>
#include <bitset>

using namespace std;

/* DEBUG */
#define D(x) cerr<<__LINE__<<" "#x" "<<x<<endl
#define D_v(x) for(int i=0;i<x.size();cerr<<x[i++]<<" ")

#define ALL(x) x.begin(),x.end()
struct rec
{
  int combi;
  int upper;
};
const int n_c = 13, n_r = 13,n_d = 5,combinations = 8192,nupper = 64;

int pop_count[combinations], dp[combinations][nupper], scores[n_r][n_c], categorization[n_c];

rec previous[combinations][nupper];

int eval(const int &category,const int dices[])
{
  int c = category + 1,score = 0;
  switch (c)
  {
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
    for (int i = 0; i < n_d; ++i)
      if (dices[i] == c)
        score += c;
    break;
  case 7:
    for (int i = 0; i < n_d; ++i)
      score += dices[i];
    break;
  case 8:
    if (dices[0] == dices[2] || dices[1] == dices[3] ||
        dices[2] == dices[4])
      for (int i = 0; i < n_d; ++i)
        score += dices[i];
    break;
  case 9:
   if (dices[0] == dices[3] || dices[1] == dices[4])
     for (int i = 0; i < n_d; ++i)
       score += dices[i];
   break;
  case 10:
    if (dices[0] == dices[4])
      score = 50;
    break;
  case 11:
    if (dices[0] == dices[1]-1 && dices[1] == dices[2]-1 &&
       dices[2] == dices[3]-1 || dices[1] == dices[2]-1 &&
       dices[2] == dices[3]-1 && dices[3] == dices[4]-1)
      score = 25;
    break;
  case 12:
    if (dices[0] == dices[1]-1 && dices[1] == dices[2]-1 &&
        dices[2] == dices[3]-1 && dices[3] == dices[4]-1)
      score = 35;
    break;
  case 13:
    if (dices[0] == dices[1] && dices[2] == dices[4] ||
        dices[0] == dices[2] && dices[3] == dices[4])
      score = 40;
    break;
  }
  return score;
}



void do_it(int& bonus, int& score)
{

  for (int i = 0; i < combinations; ++i)
    for (int j = 0; j < nupper; ++j)
      dp[i][j] = INT_MIN;

  dp[0][0] = 0;

  for (int r = 0; r < n_r; ++r)
    for (int c = 0; c < n_c; ++c)
      {
        int score = scores[r][c];
        int upper = c < 6 ? score : 0;
        for (int combi = 0, add = 1 << c; combi < combinations; ++combi)
          {
            if (pop_count[combi] != r || combi & add) continue;
            for (int u = 0; u < nupper; ++u)
              {
                int newscore = score + dp[combi][u];
                int newupper = upper + u < nupper ? upper + u : nupper - 1;
                if (newscore > dp[combi|add][newupper])
                  {
                    dp[combi|add][newupper] = newscore;
                    previous[combi|add][newupper].combi = combi;
                    previous[combi|add][newupper].upper = u;
                  }
              }
          }
      }

  int combi = combinations - 1;
  int upper = nupper - 1;
  bonus = 35;
  score = dp[combi][upper] + bonus;
  for (int u = 0; u < nupper; ++u)
    if (score < dp[combi][u])
      {
        bonus = 0;
        score = dp[combi][u];
        upper = u;
      }

  while (combi)
    {
      rec pre = previous[combi][upper];
      int c = 0;
      for (int add = combi ^ pre.combi; add >>= 1; ++c);
      categorization[c] = dp[combi][upper] - dp[pre.combi][pre.upper];
      combi = pre.combi;
      upper = pre.upper;
    }
}

int main()
{

  /* Calcula todas las categorias de cada combinacion*/
  for (int i = 0; i < combinations; ++i)
    pop_count[i] = __builtin_popcount(i);

  int dices[n_d];
  int d = 0, r = 0, g = 0;
  while (scanf("%d",&dices[d++ % n_d]) == 1)
    {
      if (d / n_d > r)
        {
          sort(dices, dices + n_d);
          for (int c = 0; c < n_c; ++c)
            scores[r % n_r][c] = eval(c,dices);

          r = d / n_d;
        }
      if (r / n_r > g)
        {
          g = r / n_r;
          int bonus = 0;
          int score = 0;
          do_it(bonus, score);
          for (int c = 0; c < n_c; ++c)
            printf("%d ",categorization[c]);

          printf("%d %d\n",bonus,score);
        }
    }

  return 0;
}


