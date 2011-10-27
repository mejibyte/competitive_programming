puts 100
100.times do
  d = rand(256)
  i = rand(256)
  m = rand(256)
  n = 100

  puts "#{d} #{i} #{m} #{n}"
  100.times do 
    print rand(256)
    print " "
  end
  puts
end

