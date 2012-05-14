srand("monkey".hash)

n = 60
m = 60
r = 10**5

puts  "#{n} #{m} #{r}"
m.times do
  
  for i in 0..n-1 do
    for j in 0..n-1 do
      if i == j
        print "0 "
      else
        print rand(10**6 + 1)
        #print 10**6
        print " "
      end
    end
    puts
  end
end


r.times do
  for 
  #k = rand(1001)
  k = 950 + rand(51)
  puts "#{s} #{f} #{k}"
end