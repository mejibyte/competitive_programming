puts 100

99.times do
print "1000 "
1000.times do |i|
  print " " if (i > 0)
  print (rand * 10**50).to_i
end
puts
end


print "1000 "
1000.times do |i|
  print " " if (i > 0)
  print(i % 2 == 0 ? 1 : 5)
end
puts
