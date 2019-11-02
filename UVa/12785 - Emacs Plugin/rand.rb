s = 10000.times.map { (rand('c'.ord - 'a'.ord) + 'a'.ord).chr }.join
n = 50

puts n
puts s
cases = 50.times do
  p = s.clone
  3.times do
    i, j = [rand(p.size), rand(p.size)].sort
    p[i, j] = "*"
  end
  puts p
end
