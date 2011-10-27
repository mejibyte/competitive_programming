n = 100
puts n
seen = { }
n.times do 
  begin
    x = rand(10 + 1) * (rand(2) > 0 ? -1 : 1)
    y = rand(10 + 1) * (rand(2) > 0 ? -1 : 1)
  end until seen[[x, y]].nil?
  seen[[x, y]] = true
  puts "#{x} #{y}"
end
puts 0