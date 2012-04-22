10.times do
  n = 50_000
  puts n
  
  previous_year = -10**9
  n.times do
    y = previous_year + rand(10000)
    rain = rand(10**9) + 1
    puts "#{y} #{rain}"
    
    previous_year = y
  end
  
  m = 10_000
  puts m
  m.times do
    y1 = rand(10**9 + 1) * (rand(2) == 0 ? 1 : -1)
    y2 = rand(10**9 + 1) * (rand(2) == 0 ? 1 : -1)
    y1, y2 = y2, y1 if y2 < y1
    puts "#{y1} #{y2}"
  end
end
puts "0 0"