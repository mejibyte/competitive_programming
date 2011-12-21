n, m = 1000, 1000


def generate
  max = 1_000
  
  x = 10
  x = rand(max - 1) + 1 while (x % 5 == 0  or x % 2 == 0)
  x
end

puts n
puts n.times.map { generate }.join(" ")

puts m
puts m.times.map { generate }.join(" ")