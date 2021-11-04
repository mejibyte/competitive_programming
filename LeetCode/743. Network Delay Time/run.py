from solution import Solution

def assert_equal(want, got):
  if want != got:
    print("FAIL: got {}, want {}".format(got, want))
  else:
    print("PASS: got {}".format(got))

assert_equal(2, Solution().networkDelayTime(
  times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2,
))

assert_equal(1, Solution().networkDelayTime(
  times = [[1,2,1]], n = 2, k = 1,
))

assert_equal(-1, Solution().networkDelayTime(
  times = [[1,2,1]], n = 2, k = 2,
))
