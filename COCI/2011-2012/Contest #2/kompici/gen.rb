n = 1_000_000

puts n
n.times do
  x = rand(10 ** 18) + 1
  puts x
end

