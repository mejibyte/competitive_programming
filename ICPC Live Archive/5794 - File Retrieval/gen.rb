def r(len)
  len.times.collect { ('a'.ord + rand(26)).chr }.join
end

1.times do
  f = 10
  puts f
  f.times do
    len = rand(10) + 2
    puts r(len)
  end
end

puts 0