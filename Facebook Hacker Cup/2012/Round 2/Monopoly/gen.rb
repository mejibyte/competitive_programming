def print_case(n, d)
  puts "#{n} #{d}"
  (n - 1).times do |i|
    puts "1 #{i + 2}"
  end
end

t = 20
puts t
t.times do |i|
  print_case(30_000, i + 1)
end

