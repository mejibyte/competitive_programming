n = 400
puts n
n.times do
  n.times do
    d = rand(1001) * (rand(2) == 0 ? +1 : -1)
    print "#{d} "
  end
  puts
end