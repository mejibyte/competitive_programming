n = 100
puts n
n.times do
  a = rand(101)
  b = rand(101)
  a, b = b, a if b < a
  puts a
  puts b
end
