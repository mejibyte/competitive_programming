100.times do |i|
  puts "#{i}..."
  system "./gen > rand.in"
  system "./a < rand.in > rand.out"
  system "java cookie < rand.in > java.out"
  system  "diff rand.out java.out"
  if !$?.success?
    exit 0
  end
end