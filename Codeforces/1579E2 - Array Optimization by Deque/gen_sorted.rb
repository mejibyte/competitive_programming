def random_int(a, b)
  a = a.to_i
  b = b.to_i
  return a + rand(b - a)
end

t = 1
puts t
t.times do
  n = 20_000
  puts n
  puts n.times.map { |i| (n - i).to_s }.join(" ")
end