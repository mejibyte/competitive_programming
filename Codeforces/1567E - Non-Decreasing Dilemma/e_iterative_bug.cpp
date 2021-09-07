#include <bits/stdc++.h>

#define D(x) cerr << #x " is " << (x) << endl

using namespace std;

typedef int64_t int64;

const int MAXN = 200000;

namespace tree {
int n;
int length[2*MAXN];
int first[2*MAXN];
int last[2*MAXN];
int prefix[2*MAXN];
int suffix[2*MAXN];
int64 pairs[2*MAXN];

void combine(int i) {
  int left = 2*i;
  int right = 2*i + 1;

  length[i] = length[left] + length[right];
  first[i] = first[left];
  last[i] = last[right];
  pairs[i] = pairs[left] + pairs[right];
  prefix[i] = prefix[left];
  suffix[i] = suffix[right];

  if (last[left] <= first[right]) {
    pairs[i] += int64(suffix[left]) * int64(prefix[right]);
    if (prefix[left] == length[left]) {
      prefix[i] = length[left] + prefix[right];
    }
    if (suffix[right] == length[right]) {
      suffix[i] = suffix[left] + length[right];
    }
  }
}

void build_initial_tree(int n) {
  tree::n = n;
  for (int i = n - 1; i >= 1; --i) {
    combine(i);
  }
}

// at should be 0-based.
void assign(int at, int value) {
  int i = n+at;
  first[i] = last[i] = value;
  for (i /= 2; i >= 1; i /= 2) {
    combine(i);
  }
}

// both inclusive
int64 query(int left, int right) {
  fprintf(stderr, "query left=%d to right=%d\n", left, right);
  left += n;
  right += n;
  int64 answer = 0;
  for (; left <= right and left > 0 and right > 0; left /= 2, right /= 2) {
    if (left % 2 == 1) {
      fprintf(stderr, "added pairs[left=%d] = %lld\n",left, pairs[left]);
      answer += pairs[left++];
    }

    if (right % 2 == 0) {
      fprintf(stderr, "added pairs[right=%d] = %lld\n",right, pairs[right]);
      answer += pairs[right--];
    }
  }
  fprintf(stderr, "result is %ld\n", answer);
  return answer;
}

} // namespace tree

int main() {
  int n, q;
  cin >> n >> q;

  // Read leaves
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;

    tree::first[n+i] = x;
    tree::last[n+i] = x;
    tree::length[n+i] = 1;
    tree::prefix[n+i] = 1;
    tree::suffix[n+i] = 1;
    tree::pairs[n+i] = 1;
  }
  tree::build_initial_tree(n);

  while (q--) {
    int type, x, y;
    cin >> type >> x >> y;
    if (type == 1) {
      x--;
      // Update a[x] to become y
      tree::assign(x, y);
    } else if (type == 2) {
      x--, y--;
      // Count valid sequences in subarray a[x, y].
      fprintf(stderr, "querying from (%d, %d)\n", x, y);
      cout << tree::query(x, y) << endl;
    }
  }

  for (int i = 1; i <= 9; i++) {
    D(i);
    D(tree::first[i]);
    D(tree::last[i]);
    D(tree::length[i]);
    D(tree::prefix[i]);
    D(tree::suffix[i]);
    D(tree::pairs[i]);
  }

  return 0;
}
