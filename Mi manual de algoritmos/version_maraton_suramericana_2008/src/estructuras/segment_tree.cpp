/*
  Range minimum query (RMQ) segment tree
 */
class SegmentTree{
  vector<int> tree;
  int n;

  void update(int root, int tree_left, int tree_right, int where, int what){
    //We assume root > 0
    if (what < tree[root]) tree[root] = what;
    if (tree_left < tree_right){
      int tree_mid = (tree_left + tree_right) / 2;
      if (where <= tree_mid){
        update(2*root, tree_left, tree_mid, where, what);
      }else{
        update(2*root + 1, tree_mid + 1, tree_right, where, what);
      }
    }
  }

  int query(int root, int tree_left, int tree_right, int query_left, int query_right){
    if (query_right >= n) return query(root, tree_left, tree_right, query_left, n-1);
    if (query_left > query_right) return INT_MAX; //Retornar elemento identidad
    if (tree_left == query_left && tree_right == query_right) return tree[root];

    int tree_mid = (tree_left + tree_right) / 2;

    int leftSide = query(2*root, tree_left, tree_mid, query_left, min(query_right, tree_mid));
    int rightSide = query(2*root + 1, tree_mid+1, tree_right, max(query_left, tree_mid+1), query_right);

    return min(leftSide, rightSide);
  }

public:
  SegmentTree(int max_n) : n(max_n), tree(4 * max_n + 1, INT_MAX) {
    /*
      Llenarlo inicialmente con el elemento identidad.
      Para la función mínimo, la identidad es infinito.
    */
  }

  /*
    Retorna el mínimo elemento en el intervalo [from, to].
   */
  int query(int from, int to){
    if (from < 0) from = 0;
    if (to >= n) to = n-1;
    return query(1, 0, n-1, from, to);
  }

  /*
    Cambia el elemento en la posición where por what.
   */
  void update(int where, int what){
    if (where < n) update(1, 0, n-1, where, what);
  }

};

int main(){
  int n = 15;
  vector<int> v(n);
  SegmentTree tree(n);
  for (int i=0; i<n; ++i){
    int x = random()%20;
    printf("%d ", x);
    v[i] = x;
    tree.update(i, x);
  }
  printf("\n");

  int left, right;
  while (cin >> left >> right){
    printf("El mínimo elemento entre [%d, %d] es %d.\n", left, right, tree.query(left, right));
  }

  return 0;
}

