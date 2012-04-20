t = 100
100.times do
  n = 5
  puts n
  n.times do
    x = rand(10) * (rand(2) == 0 ? +1 : -1)
    print x
    print " "
  end
  puts
end