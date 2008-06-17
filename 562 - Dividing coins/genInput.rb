puts "31"
puts "100"
s = ""
100.times do
  s += "500 "
end
puts s.chop!

30.times do
  puts "100"
  s = ""
  100.times do
    s += (1 + rand(500)).to_s + " "
  end
  puts s.chop!
end
