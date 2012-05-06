1.times do
  system "ruby gen.rb > rand.in"
  system "./arrange.2 < rand.in"
  unless $?.success?
    exit 0
  end
end