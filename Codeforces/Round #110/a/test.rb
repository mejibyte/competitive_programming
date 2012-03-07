20.times do |i|
  puts "test #{i}..."
  system "ruby gen.rb > rand.in"
  system "./a < rand.in > correct"
  system "./a.wrong < rand.in > incorrect"
  system "diff correct incorrect"
  unless $?.success?
    exit 0
  end
end