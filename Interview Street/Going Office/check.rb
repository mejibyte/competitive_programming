100.times do |i|
  puts "#{i}..."
  
  system "ruby gen.rb > rand.in"
  system "./brute < rand.in > correct.out"
  system "./office < rand.in > wrong.out"
  exit -1 unless $?.success?
  
  system "diff correct.out wrong.out"
  unless $?.success?
    exit -1
  end
end