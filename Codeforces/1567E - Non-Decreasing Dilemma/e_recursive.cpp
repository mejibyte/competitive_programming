// This one seems to be correct but gets TLE. I have no fucking idea why and
// gave up trying to profile this with Valgrind.
#include <bits/stdc++.h>
#include <chrono>
using namespace std::chrono;

#define D(x) cerr << #x " is " << (x) << endl

// #ifdef LOCAL
// #define dassert(x) assert(x)
// #else
// #define dassert(x)
// #endif

#define dassert(x)

using namespace std;

typedef int64_t int64;

const int MAXN = 200000;

namespace tree {
int n;
int length[4*MAXN];
int first[4*MAXN];
int last[4*MAXN];
int prefix[4*MAXN];
int suffix[4*MAXN];
int64 pairs[4*MAXN];

void combine(int i) {
  int left = 2*i+1;
  int right = 2*i+2;

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

void initialize(const vector<int> &a, int u, int ul, int ur) {
  // Leaf
  if (ul == ur) {
    first[u] = a[ul];
    last[u] = a[ul];
    length[u] = 1;
    prefix[u] = 1;
    suffix[u] = 1;
    pairs[u] = 1;
    return;
  }

  // Non-leaf
  int mid = ul + (ur - ul) / 2;
  initialize(a, 2*u+1, ul, mid);
  initialize(a, 2*u+2, mid+1, ur);

  combine(u);
}


// at should be 0-based.
void assign(int u, int ul, int ur, int at, int value) {
  assert(ul <= at and at <= ur);

  // Leaf
  if (ul == ur) {
    assert(ul == at and at == ur);
    first[u] = value;
    last[u] = value;
    length[u] = 1;
    prefix[u] = 1;
    suffix[u] = 1;
    pairs[u] = 1;
    return;
  }

  // Non-leaf
  int mid = ul + (ur - ul) / 2;
  if (ul <= at and at <= mid) {
    assign(2*u+1, ul, mid, at, value);
  } else {
    assign(2*u+2, mid+1, ur, at, value);
  }

  combine(u);
}

// both inclusive
int64 query(int u, int ul, int ur, int left, int right) {
  dassert(ul <= left and left <= right and right <= ur);
  if (ul == ur) {
    dassert(ul == ur and ur == left and left == right);
    dassert(pairs[u] == 1);
    return pairs[u];
  }
  int mid = ul + (ur - ul) / 2;
  if (right <= mid) {
    // Entirely included on my left child. Delegate to him.
    return query(2*u+1, ul, mid,    left, right);
  }

  if (mid+1 <= left) {
    // Entirely included on my right child. Delegate to him.
    return query(2*u+2, mid+1, ur,   left, right);
  }

  dassert(left <= mid and mid+1 <= right);
  int64 answer = 0;
  answer += query(2*u+1, ul, mid,      left, mid);
  answer += query(2*u+2, mid+1, ur,    mid+1, right);

  // Now count pairs that cross between halves.
  if (last[2*u+1] <= first[2*u+2]) {
    int64 length_left = min(suffix[2*u+1], mid - left + 1);
    int64 length_right = min(prefix[2*u+2], right - (mid+1) + 1);
    answer += length_left * length_right;
  }


  return answer;
}

} // namespace tree

int main() {
  int n, q;
  scanf("%d %d", &n, &q);

  // Read leaves
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    int x;
    scanf("%d", &a[i]);
  }

  auto start = high_resolution_clock::now();
  tree::initialize(a, 0, 0, n-1);
  auto elapsed = duration_cast<microseconds>(high_resolution_clock::now() - start);
  cerr << "initialize took " << elapsed.count() << "us" << endl;

  long long total_update_usec = 0;
  long long total_query_usec = 0;

  while (q--) {
    int type, x, y;
    scanf("%d %d %d", &type, &x, &y);
    if (type == 1) {
      x--;
      // Update a[x] to become y
      auto start = high_resolution_clock::now();
      tree::assign(0, 0, n-1, x, y);
      auto elapsed = duration_cast<microseconds>(high_resolution_clock::now() - start);
      total_update_usec += elapsed.count();
    } else if (type == 2) {
      x--, y--;
      // Count valid sequences in subarray a[x, y].
      auto start = high_resolution_clock::now();
      int64 answer = tree::query(0, 0, n-1, x, y);
      auto elapsed = duration_cast<microseconds>(high_resolution_clock::now() - start);
      total_query_usec += elapsed.count();

      printf("%lld\n", answer);
    }
  }

  cerr << "total_update_usec: " << total_update_usec << endl;
  cerr << "total_query_usec: " << total_query_usec << endl;
  return 0;
}
