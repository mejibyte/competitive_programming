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
#include <map>
#include <set>

int numbers[100001];
int a[50005], b[50005];
int n;


/*
  Sorts the elements from numbers [start ... end) in decreasing order
  and returns the number of inversions in that piece of array.
*/
long long merge_sort(int start, int end){
  long long cnt = 0;
  if (start + 1 == end){ //Single element
    return cnt;
  }

  int m = (start + end)/2;
  cnt += merge_sort(start, m) + merge_sort(m, end);

  int _a = m - start, _b = end - m;
  for (int i=start; i<start+_a; ++i){
    a[i-start] = numbers[i];
  }
  
  for (int i=m; i<m+_b; ++i){
    b[i-m] = numbers[i];
  }

  for (int i=0, j=0; i<_a && j<_b; ){
    if (a[i] > b[j]){
      cnt += (long long)(_b - j);
      ++i;
    }else{
      ++j;
    }
  }

  a[_a] = b[_b] = -1;

  for (int k=start, i=0, j=0; k<end; ++k){
    if (a[i] > b[j]){
      numbers[k] = a[i++];
    }else{
      numbers[k] = b[j++];
    }
  }

  return cnt;
}


int main(){
  while (scanf("%d", &n)==1 && n){
    for (int i=0; i<n; ++i){
      scanf("%d", &numbers[i]);
    }

    long long cnt = merge_sort(0, n);
    //printf("%lld\n", cnt);
    puts((cnt % 2 ? "Marcelo" : "Carlos"));
  }
  return 0;
}


