20.times do |i|
  puts "Test #{i}..."
  
  system "ruby gen.rb > rand.in"
  system "./bruteforce < rand.in > right.out"
  exit -1 unless $?.success?
  system "./j.6 < rand.in > wrong.out"
  system "diff right.out wrong.out"
  unless $?.success?
    puts
    puts "*" * 10
    puts 
    system "cat rand.in"
    system "rm right.out wrong.out"    
    exit -1
  end
end
system "rm right.out wrong.out"
