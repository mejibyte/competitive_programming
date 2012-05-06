n = 30
m = rand(n * (n - 1) / 2) + 1
puts "#{n} #{m}"

edges = []

m.times do
  u = rand(n)
  v = rand(n)
  while u == v or edges.index([u, v]) or edges.index([v, u])
    u = rand(n)
    v = rand(n)
  end
  edges << [u, v]
  w = rand(1000) + 1
  puts "#{u} #{v} #{w}"
end

u = rand(n)
v = rand(n)
while u == v
  u = rand(n)
  v = rand(n)
end
puts "#{u} #{v}"

q = edges.size
puts q
q.times do |i|
  e = edges[i]
  puts "#{e[0]} #{e[1]}"
end