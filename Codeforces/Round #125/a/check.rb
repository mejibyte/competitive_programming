100.times do |i|
  puts i
  system "ruby gen.rb > rand.in"
  system "./a < rand.in"
  #system "./brute < rand.in > brute.out"
  #system "diff a.out brute.out"
  #if !$?.success?
  #  exit 0
  #end
end