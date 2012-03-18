k = 2000
s = 100.times.map { 'a' }.join

puts k
puts s
q = 20_000
puts q
q.times do |i|
  puts "#{k*s.size - i} a"
end