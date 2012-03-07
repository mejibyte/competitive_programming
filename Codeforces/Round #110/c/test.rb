20.times do |i|
  puts "test #{i}..."
  system "ruby gen.rb > rand.in"
  system "./c.2 < rand.in > correct"
  system "./challenge < rand.in > incorrect"
  system "diff correct incorrect"
  unless $?.success?
    exit 0
  end
end