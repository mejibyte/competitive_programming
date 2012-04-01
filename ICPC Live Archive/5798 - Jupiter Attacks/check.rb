10.times do |i|
  puts "Test #{i}..."
  
  system "ruby gen.rb > rand.in"
  system "./bruteforce < rand.in > right.out"
  system "./jupiter < rand.in > wrong.out"
  system "diff right.out wrong.out"
  unless $?.success?
    exit -1
    system "rm right.out wrong.out"
  end
end
system "rm right.out wrong.out"
