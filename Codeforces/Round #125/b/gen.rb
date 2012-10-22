n = 10**5
k = rand(n) + 1

s1 = n.times.map {  rand(3) == 0 ? "X" : "-" }.join
s2 = n.times.map {  rand(3) == 0 ? "X" : "-" }.join

puts "#{n} #{k}"
puts s1
puts s2