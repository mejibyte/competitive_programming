1000.times do
  
  n = rand(10) + 2
  puts n
  s = rand(n) + 1
  t = rand(n) + 1
  t = rand(n) + 1 while s == t
  c = rand([n * n, 10].min)
  puts "#{s} #{t} #{c}"
  
  c.times do
    u = rand(n) + 1
    v = rand(n) + 1
    v = rand(n) + 1 while u == v
    w = rand(21)
    puts "#{u} #{v} #{w}"
  end
  
end

puts 0