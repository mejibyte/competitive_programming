srand(0x1337)

n = 5_000
puts n
n.times.map { rand(10e9 + 1) }.sort.each do |i|
  puts i
end