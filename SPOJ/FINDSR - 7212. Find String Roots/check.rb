100.times do |i|
  puts "Test #{i}..."
  system "ruby gen.rb > rand.in"
  system "./str < rand.in > correct.out"
  system "./str.2 < rand.in > wrong.out"
  system "diff correct.out wrong.out"
  exit if !$?.success?
end