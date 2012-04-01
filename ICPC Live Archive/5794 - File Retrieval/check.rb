50.times do |i|
  puts "Test #{i}..."
  system "ruby gen.rb > rand.in"
  system "./bruteforce < rand.in > correct.out"
  system "./file.6 < rand.in > wrong.out"
  system "diff correct.out wrong.out"
  unless $?.success?
    system "rm wrong.out correct.out"
    exit -1
  end
end
system "rm wrong.out correct.out"

