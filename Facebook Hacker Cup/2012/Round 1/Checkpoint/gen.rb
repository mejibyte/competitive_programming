n = 10000
a = (1..1000).to_a
b = ((10 ** 7 - 1000)..10**7).to_a
puts n + a.size + b.size
puts a.join("\n")
puts b.join("\n")
n.times do
  puts rand(10_000_000) + 1
end