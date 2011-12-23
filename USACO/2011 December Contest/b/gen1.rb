n = 10
m = 100_000
while m % 3 != 0
  m -= 1
end
puts "#{n} #{m}"

max = 0

times = {}
1.upto(1_000_000) { |w| times[w] = 0 }

1.upto(m / 3) do |i|
  u = (i - 1) % n + 1
  v = (i % n) + 1

  puts "#{u} #{v} #{i}"
  
  v = (i + 1) % n + 1
  puts "#{u} #{v} #{i}"
  v = (i + 2) % n + 1
  puts "#{u} #{v} #{i}"
end
