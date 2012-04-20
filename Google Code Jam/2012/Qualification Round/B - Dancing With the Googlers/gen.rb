t = 100
puts t
t.times do
  n = rand(100) + 1
  s = rand(n + 1)
  p = rand(11)
  
  print "#{n} #{s} #{p} "
  n.times do
    k = rand(28 - 2 + 1) + 2
    print "#{k} "
  end
  puts
end