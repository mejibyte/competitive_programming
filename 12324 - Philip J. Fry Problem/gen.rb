n = 4
100.times do
  puts n
  n.times do
    t = rand(50) * 2
    b = rand(3)
    puts "#{t} #{b}"
  end
end
puts 0