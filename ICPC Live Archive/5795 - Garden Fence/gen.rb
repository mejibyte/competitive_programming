def r(x)
  rand(x) * (rand(2) == 0 ? +1 : -1)
end

def point
  a = [r(10**5 + 1), r(10**5 + 1), (1).abs]
  a = [r(10**5 + 1), r(10**5 + 1), (1).abs] while @seen[a]
  @seen[a] = true
  a
end

1.times do
  @seen = {}
  p = 1
  q = 1000
  puts "#{p} #{q}"
  p.times do
    puts point.join(" ")
  end
  q.times do
    puts point.join(" ")
  end
end
puts "0 0"