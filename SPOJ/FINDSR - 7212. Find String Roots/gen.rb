def random_string(len)
  len.times.map { (rand(26) + "a".ord).chr }.join("")
end

1.times do
  puts random_string(rand(10) + 1)
end
puts "*"
