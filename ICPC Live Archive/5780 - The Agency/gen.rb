runs = 1

runs.times do
  n = 10
  puts n
  puts n.times.map { rand(2).to_s }.join
  puts n.times.map { rand(2).to_s }.join
  
  puts n.times.map { rand(20) + 1 }.sort_by { |x| -x }.join(" ")
end

puts 0