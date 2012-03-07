n = 100_000
puts n
n.times do
  x = rand(100)
  s = rand(2) == 0 ? +1 : -1
  print x*s
  print " "
end
puts