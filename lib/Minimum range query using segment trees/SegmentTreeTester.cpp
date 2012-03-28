#include "SegmentTree.cpp"

#include <cstdlib>
#include <cstdio>
#include <cassert>

SegmentTree t;

void build_random_tree(int n = 100){
  t.arr.resize(n);
  for (int i=0; i<n; ++i) t.arr[i] = random() * (random() % 2 ? -1 : 1);
  t.initialize();
}

void check_query_correctness(int u, int v){
  assert(u <= v);
  int index = u;
  for (int k=u; k<=v; ++k) if (t.arr[k] < t.arr[index]) index = k;
  int q = t.query(u, v);
  printf("Range [%d, %d]:\n", u, v);
  printf("     Tree query: index = %d, element = %d\n", q, t.arr[q]);
  printf("   Linear query: index = %d, element = %d\n", index, t.arr[index]);
  assert(index == q);
  printf("      SUCCESS\n");
}

void check_random_queries(int times = 100){
  while (times--){
    int u = random() % t.n, v = random() % t.n;
    if (v < u) swap(u, v);
    check_query_correctness(u, v);
  }
}

void check_update_correctness(int where, int what){
  vector<int> old = t.arr;
  t.update(where, what);

  old[where] = what;
  printf("Update [%d] = %d\n", where, what);
  assert(t.arr == old);
  printf("      SUCCESS\n");
}

void check_random_updates(int times = 100){
  while (times--){
    int where = random() % t.n, what = random() * (random() % 2 ? -1 : 1);
    check_update_correctness(where, what);
    //after an update, check some random queries to see if everything remains fine.
    check_random_queries();
  }
}

void print_array(const vector<int> &arr){
  for (int i=0; i<arr.size(); ++i) printf("%d ", arr[i]);
  printf("\n");
}

int main(){
  int n = 10;
  build_random_tree(n);
  check_random_queries(2*n);
  check_random_updates();
  return 0;
}
