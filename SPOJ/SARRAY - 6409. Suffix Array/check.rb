100.times do |i|
  puts "Test #{i}..."
  system "ruby gen.rb > rand.in"
  system "./sarray.2 < rand.in > good.out 2> /dev/null"
  system "./sarray < rand.in > bad.out 2> /dev/null"
  system "diff good.out bad.out"
  if !$?.success?
    exit -1
  end
end