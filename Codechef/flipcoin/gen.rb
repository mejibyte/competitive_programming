n = 4
q = 100
puts "#{n} #{q}"
q.times do
  u = rand(n)
  v = rand(n)
  u, v = v, u if v < u
  
  puts "#{rand(2)} #{u} #{v}"
end