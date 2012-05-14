t = 1
puts t
t.times do
  n = 1000
  puts n
  n.times do
    a = rand(10)
    b = rand(10)
    a, b = b, a if b < a
    puts "#{a} #{b}"
  end
end