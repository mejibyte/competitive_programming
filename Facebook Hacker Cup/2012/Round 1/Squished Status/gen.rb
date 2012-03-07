n = 1000
puts n
n.times do
  len = rand(255) + 1
  puts len
  len.times do
    print rand(9)
  end
  puts
end