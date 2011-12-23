n = 10
m = 100_000
puts "#{n} #{m}"

max = 0

times = {}
1.upto(1_000_000) { |w| times[w] = 0 }

1.upto(m) do |i|
  u = (i - 1) % n + 1
  v = (i % n) + 1
  
  w = rand(1_000_000) + 1
  while times[w] == 3
    w = rand(1_000_000) + 1
  end
  
  times[w] += 1
  max = [max, times[w]].max
  puts "#{u} #{v} #{w}"
end

STDERR.puts "Max: #{max}"