t = 1
puts t

t.times do
  n = 50
  puts n
  g = n.times.map { Array.new(n) }
  for i in 0..(n - 1) 
    for j in (i + 1)..(n - 1)
      r = rand(2)
      g[i][j] = r
      g[j][i] = 1 - r
    end
    g[i][i] = 0
  end
  
  for i in 0..(n - 1) 
    for j in 0..(n - 1)
      print g[i][j]
    end
    puts
  end
  
end