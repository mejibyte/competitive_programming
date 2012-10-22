t = 10
puts t
t.times do
  
  n = 10_000
  love = 2*n + 1
  puts n
  dists = n.times.map { |i| 2*i + 1 }.sort
  lens = n.times.map { 10**9 }
  n.times do |i|
    puts "#{dists[i]} #{lens[i]}"
  end
  puts love
  
end