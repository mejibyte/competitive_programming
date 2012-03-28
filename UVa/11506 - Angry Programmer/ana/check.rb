30.times do |i| 
  puts "Test case #{i}..."
  system "ruby gen.rb > rand.in"
  system "./ac < rand.in > right.out"
  system "./ana < rand.in > wrong.out"
  system "diff right.out wrong.out"
  unless $?.success?
    break
  end
end
system "rm right.out wrong.out"