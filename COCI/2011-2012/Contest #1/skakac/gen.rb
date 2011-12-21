m = []
30.times { m << Array.new(30, 3) }

m[1][2] = 1
m[3][3] = 2

puts "30 999998"
puts "1 1"
30.times do |i|
  30.times do |j|
    print m[i][j]
    print " "
  end
  puts
end