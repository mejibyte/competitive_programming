#include <vector>
using namespace std;

class SegmentTree{
public:
  vector<int> arr, tree;
  int n;

  SegmentTree(){}
  SegmentTree(const vector<int> &arr) : arr(arr) {
    initialize();
  }

  //must be called after assigning a new arr.
  void initialize(){
    n = arr.size();
    tree.resize(4*n + 1);
    initialize(0, 0, n-1);
  }

  int query(int query_left, int query_right) const{
    return query(0, 0, n-1, query_left, query_right);
  }

  void update(int where, int what){
    update(0, 0, n-1, where, what);
  }

private:
  int initialize(int node, int node_left, int node_right);
  int query(int node, int node_left, int node_right, int query_left, int query_right) const;
  void update(int node, int node_left, int node_right, int where, int what);
};

int SegmentTree::initialize(int node, int node_left, int node_right){
  if (node_left == node_right){
    tree[node] = node_left;
    return tree[node];
  }
  int half = (node_left + node_right) / 2;
  int ans_left = initialize(2*node+1, node_left, half);
  int ans_right = initialize(2*node+2, half+1, node_right);

  if (arr[ans_left] <= arr[ans_right]){
    tree[node] = ans_left;
  }else{
    tree[node] = ans_right;
  }
  return tree[node];
}

int SegmentTree::query(int node, int node_left, int node_right, int query_left, int query_right) const{
  if (node_right < query_left || query_right < node_left) return -1;
  if (query_left <= node_left && node_right <= query_right) return tree[node];

  int half = (node_left + node_right) / 2;
  int ans_left = query(2*node+1, node_left, half, query_left, query_right);
  int ans_right = query(2*node+2, half+1, node_right, query_left, query_right);

  if (ans_left == -1) return ans_right;
  if (ans_right == -1) return ans_left;

  return (arr[ans_left] <= arr[ans_right] ? ans_left : ans_right);
}

void SegmentTree::update(int node, int node_left, int node_right, int where, int what){
  if (where < node_left || node_right < where) return;
  if (node_left == where && where == node_right){
    arr[where] = what;
    tree[node] = where;
    return;
  }
  int half = (node_left + node_right) / 2;
  if (where <= half){
    update(2*node+1, node_left, half, where, what);
  }else{
    update(2*node+2, half+1, node_right, where, what);
  }
  if (arr[tree[2*node+1]] <= arr[tree[2*node+2]]){
    tree[node] = tree[2*node+1];
  }else{
    tree[node] = tree[2*node+2];
  }
}
