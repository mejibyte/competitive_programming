left = 100
n = 4

letters = "abcdefg"

n.times do |i|
  len = rand(left - (n - i)) + 1
  s = len.times.collect { |i| letters[rand(letters.size)] }.join
  puts "#{len} #{s}"
  left -= len
end