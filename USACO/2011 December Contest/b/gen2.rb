groups = 12_000 
n = 3 * groups + 1
m = 4 * groups

puts "#{n} #{m}"

nextEdge = 1
nextNode = 2

groups.times do
  
  a = nextNode
  b = nextNode + 1
  c = nextNode + 2
  
  puts "%d %d %d" % [a, b, nextEdge]
  puts "%d %d %d" % [a, c, nextEdge]
  puts "%d %d %d" % [b, c, nextEdge]
  puts "%d %d %d" % [a, 1, nextEdge + 1]
  
  nextNode = c + 1
  nextEdge += 2
end
