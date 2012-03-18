n = 1000

# puts n
# n.times do |i|
#   puts (i + 1).times.map { 1 }.join(" ")
# end

puts n
n.times do |i|
  puts (i + 1).times.map { rand(10**5 + 1) * (rand(2) == 0 ? -1 : +1) }.join(" ")
end

puts 0