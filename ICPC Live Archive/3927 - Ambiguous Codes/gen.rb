n = 100
puts n
n.times do
  len = rand(50) + 1
  len.times do
    print rand(16).to_s(16).capitalize
  end
  puts
end
puts 0