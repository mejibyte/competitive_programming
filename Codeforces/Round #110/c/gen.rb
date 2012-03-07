def getString(len)
  s = ""
  len.times do |i|
    s += ('a'.ord + rand(26)).chr
  end
  s
end


n = rand(10) + 1
m = rand(5) + 1
puts getString(n)
puts getString(m)