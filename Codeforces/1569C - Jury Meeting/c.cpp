#include <iostream>
#include <algorithm>
using namespace std;

const int N = 2e5 + 100;

typedef int64_t int64;

const int64 mod = 998244353;

struct Integer {
  int64 value;
  Integer(int64 value = 0) : value(value) {}
};

Integer operator *(const Integer &a, const Integer &b) {
  return Integer(a.value * b.value % mod);
}

Integer factorial[N];
int a[N];

// Modular exponentiation. Returns x^y (mod mod).
// We use it to find the multiplicative modular inverse modulo mod using
// Euler's Totient Theorem. This theorem states that if y is prime, then
// x^(y-2) == 1 (mod y).
Integer pow(Integer x, Integer y = mod - 2) {
  Integer result(1);
  while (y.value > 0) {
    if(y.value & 1)
      result = result * x;
    x = x * x;
    y.value >>= 1;
  }
  return result;
}

// Returns n Choose k modulo mod.
Integer choose(int n, int k) {
  // n! / k! / (n-k)!
  return factorial[n] * pow(factorial[k]) * pow(factorial[n-k]);
}

void solve(int n) {
  sort(a, a + n);
  reverse(a, a + n);

  if (a[0] - a[1] > 1) {
    // In this case, no matter what, the a[0] juror will always tell two tasks
    // in a row at the very end.
    cout << 0 << endl;
    return;
  }
  if (a[0] == a[1]) {
    // In this case, no matter what, the a[0] and a[1] will battle until the
    // very end and then each tell their last task in the last round.
    cout << factorial[n].value << endl;
    return;
  }

  // At this point, we know the following:
  //
  // - a[0] is the maximum and it's unique (all other jurors must have less than
  //   a[0] tasks or we would have returned in the a[0] == a[1] if statement
  //   above). Let's imagine the one and only juror with a[0] tasks is called
  //   Max.
  // - There is at least one juror with a[0]-1 tasks (namely a[1]), but there
  //   may be more than one.
  // - A permutation is nice if and only if there is at least one juror with
  //   a[0]-1 tasks that appears to the right of wherever Max appears.
  //   In this case those Max and that juror will battle until the end; at the
  //   Max will have 1 remaining task and the other juror will have 0 and Max
  //   will be able to finish without ever telling two tasks in a row.

  int good = 0; // Number of jurors with a[0]-1 tasks
  int bad = 0; // Number of jurors with < a[0]-1 tasks
  for (int i = 0; i < n; ++i) {
    if (a[i] == a[0] - 1) good++;
    else if (a[i] < a[0] - 1) bad++;
  }

  // We must place at least one good juror to the right of Max. We don't care
  // where the bad jurors are.
  //
  // So the answer is as follows:
  //  - Start with n empty slots
  //  - Choose the slots where we will place the bad jurors. There are
  //    choose(n, bad) ways to pick these slots.
  //  - Once the bad jurors get their slots, permute them however you want.
  //    There are bad! ways to do this.
  //  - We end up with n - bad available slots to place Max and the good jurors.
  //    Remember, there must be at least one good juror to the right of Max. In
  //    other words, Max can sit anywhere except the very last of these
  //    available slots.
  //  - Let's choose where Max goes. We have n - bad available slots, and he can
  //    go anywhere except the last one. So there are n-bad-1 options for Max.
  //  - We end up with n-bad-1 == good empty slots for the good jurors. It
  //    doesn't matter where they sit because we know at least one will always
  //    end up to the right of Max. So there are good! ways here.
  Integer answer = choose(n, bad) * factorial[bad] * (n - bad - 1) * factorial[good];

  cout << answer.value << endl;
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  factorial[0] = Integer(1);

  for(int i = 1 ; i < N; i++)
    factorial[i]  = factorial[i - 1] * Integer(i);

  int tt;
  cin >> tt;
  while (tt--){
    int n;
    cin >> n;
    for(int i = 0; i < n; i++)
      cin >> a[i];
    solve(n);
  }
}