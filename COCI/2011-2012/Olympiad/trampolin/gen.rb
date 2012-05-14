n = 300_000
start = rand(n)
h = n.times.map { rand(10**6) + 1 }

while start == 0 or start == n - 1 or h[start] >= h[start - 1] or h[start] >= h[start + 1]
  start = rand(n)
end

raise "WTF" unless start != 0 and start != n - 1 and h[start] < h[start - 1] and h[start] < h[start + 1]

puts "#{n} #{start + 1}"
puts h.join(" ")

n.times do
  print "."
end
puts
