#include <bits/stdc++.h>

#define D(x) cerr << #x " is " << (x) << endl

using namespace std;

typedef int64_t int64;

const int MAXN = 200000;

namespace tree {

struct Segment {
  int length;
  int first_value;
  int last_value;
  int prefix;
  int suffix;
  int64 pairs;
};

Segment data[2*MAXN];
int n;

Segment merge(const Segment& left, const Segment &right) {
  if (left.length == 0) return right;
  if (right.length == 0) return left;

  Segment answer;
  answer.length = left.length + right.length;
  answer.first_value = left.first_value;
  answer.last_value = right.last_value;
  answer.pairs = left.pairs + right.pairs; // Pairs that don't cross the middle
  answer.prefix = left.prefix;
  answer.suffix = right.suffix;

  if (left.last_value <= right.first_value) {
    // Pairs that cross the middle.
    answer.pairs += int64(left.suffix) * int64(right.prefix);

    if (left.prefix == left.length) {
      answer.prefix = left.length + right.prefix;
    }
    if (right.suffix == right.length) {
      answer.suffix = left.suffix + right.length;
    }
  }

  return answer;
}
void build_initial_tree(int n) {
  tree::n = n;
  for (int i = n - 1; i >= 1; --i) {
    data[i] = merge(data[i*2], data[i*2+1]);
  }
}

// at should be 0-based.
void assign(int at, int value) {
  int i = n+at;
  data[i] = {
    .length = 1,
    .first_value = value,
    .last_value = value,
    .prefix = 1,
    .suffix = 1,
    .pairs = 1
  };
  for (i /= 2; i >= 1; i /= 2) {
    data[i] = merge(data[i*2], data[i*2+1]);
  }
}

// both inclusive and 0-based.
Segment query(int left, int right) {
  left += n;
  right += n;
  Segment answer = {.length = 0}; // Identity.

  stack<Segment> pending; // Needed when operation is not associative.
  for (; left <= right; left /= 2, right /= 2) {
    if (left % 2 == 1) {
      answer = merge(answer, data[left++]);
    }
    if (right % 2 == 0) {
      pending.push(data[right--]);
    }
  }

  while (pending.size() > 0) {
    Segment next = pending.top();
    pending.pop();
    answer = merge(answer, next);
  }

  return answer;
}

} // namespace tree

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;
  // Read leaves
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;

    tree::data[n+i] = tree::Segment{
      .length = 1,
      .first_value = x,
      .last_value = x,
      .prefix = 1,
      .suffix = 1,
      .pairs = 1
    };
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
      tree::Segment answer = tree::query(x, y);
      cout << answer.pairs << endl;
    }
  }

  return 0;
}
