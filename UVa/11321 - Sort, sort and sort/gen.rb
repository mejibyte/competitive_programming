n = 8_000
m = 5

puts "#{n} #{m}"

n.times do
  k = rand(1000) * (rand(2) == 0 ? 1 : -1)
  puts "#{k}"
end

puts "0 0"