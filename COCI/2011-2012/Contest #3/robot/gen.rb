n = 100_000
m = 10_000
puts "#{n} #{m}"

n.times do
  x = rand(2) == 1 ? -1 : +1
  x = x * rand(1_000_000)
  y = rand(2) == 1 ? -1 : +1
  y = y * rand(1_000_000)
  puts "#{x} #{y}"
end

m.times do
  print "SJIZ"[rand(4)]
end
puts "l"
