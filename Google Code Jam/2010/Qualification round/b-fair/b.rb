require 'rubygems'

t = readline.to_i
t.times do |kase|
  print "Case #%d: " % (kase + 1)
  a = readline.split.collect { |k| k.to_i }
  a.shift

  small = a.min
  b = a.collect { |k| k - small }
  g = b.first.to_i
  1.upto(b.size - 1) do |i|
    g = g.gcd(b[i])
  end
  puts ((g - small) % g + g) % g
end


