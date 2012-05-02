1000.times do |i|
  puts "Test #{i}..."
  
  system  "ruby gen.rb > rand.in"
  system "./brute < rand.in > brute.out"
  system "./routing.2 < rand.in > fast.out"
  system "diff brute.out fast.out"
  
  exit 0 unless $?.success?
end