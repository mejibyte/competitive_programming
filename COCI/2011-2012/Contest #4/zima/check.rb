n = 100
100.times do |i|
  puts "Random case #{i}..."
  system "ruby gen.rb > rand.in"
  system "time ./zima < rand.in"
end
system "rm rand.in"