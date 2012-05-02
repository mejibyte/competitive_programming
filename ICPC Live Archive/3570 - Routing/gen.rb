n = rand(18) + 1
m = rand(n * (n + 1) / 2) + 1

edges = m.times.map do
  u = rand(n) + 1
  v = rand(n) + 1
  "#{u} #{v}"
end

edges.uniq!

m = edges.size
puts "#{n} #{m}"
puts edges.join("\n")
puts "0 0"

