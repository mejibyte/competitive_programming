1.times do
  
  m = rand(14) + 2
  w = rand(36) + 1
  puts "#{m} #{w}"
  2.upto(m-1) do |i|
    puts "#{i} #{rand(100) + 1}"
  end
  
  w.times do
    u = rand(m) + 1
    v = rand(m) + 1
    v = rand(m) + 1 while u == v
    puts "#{u} #{v} #{rand(100) + 1}"
  end
  
end
puts "0 0"