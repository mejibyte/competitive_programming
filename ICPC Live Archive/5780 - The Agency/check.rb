100.times do |i|
  puts "Test #{i}..."
  
  system "ruby gen.rb > rand.in"
  system "./brute < rand.in > rand.out"
  system "./a.2 < rand.in > wrong.out"
  system "diff wrong.out rand.out"
  
  if !$?.success?
    exit -1
  end
end