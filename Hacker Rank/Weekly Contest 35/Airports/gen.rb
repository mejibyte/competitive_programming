q = 100
puts q
q.times do
 d = rand(10)
 n = rand(8) + 2
 a = n.times.map { rand(10) }
 puts "#{n} #{d}"
 puts a.join(" ")
end
