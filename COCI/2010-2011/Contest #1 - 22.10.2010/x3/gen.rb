n = 1_000_000
puts n
n.times do
  puts rand(1_000_000 - 1) + 1
end