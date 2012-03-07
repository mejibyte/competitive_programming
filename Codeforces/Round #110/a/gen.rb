n = rand(3) + 1
puts n

n.times do |i|
  n.times do |j|
    print rand(100) + 1
    print " "
  end
  puts
end