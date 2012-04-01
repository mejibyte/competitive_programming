p = [11, 13, 139, 1000003, 999999937].sample
b = rand(p)
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
