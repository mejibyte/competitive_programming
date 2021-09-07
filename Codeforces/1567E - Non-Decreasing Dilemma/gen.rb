def random(low, high)
  low + rand(high - low + 1)
end

srand(0x20210906)

n = 1 * 30
q = 1 * 30
printf("%d %d\n", n, q)

puts n.times.map { random(1, 10**9).to_s }.join(" ")
q.times do
  if rand(2) == 0
    type = 1
    index = random(1, n)
    value = random(1, 10**9)
    printf("%d %d %d\n", type, index, value)
  else
    type = 2
    left = random(1, n)
    right = random(1, n)
    left, right = right, left if left > right
    printf("%d %d %d\n", type, left, right)
  end
end
