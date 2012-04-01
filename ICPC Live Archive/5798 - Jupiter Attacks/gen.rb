p = [11, 13, 139, 1000003, 999999937].sample
p = [3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 139, 999900961].sample
b = rand(p - 2) + 2
l = rand(10000) + 1
q = 5

puts "#{b} #{p} #{l} #{q}"

q.times do
  if rand(2) == 0
    print "E "
    
    where = rand(l) + 1
    what = rand(b)
    puts "#{where} #{what}"
    
  else
    print "H "
    from = rand(l) + 1
    to = rand(l) + 1
    from, to = to, from if to < from
    puts "#{from} #{to}"
  end
end
