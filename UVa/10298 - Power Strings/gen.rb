def f(i)
  if i == 0
    return [""]
  else
    ans = []
    old = f(i - 1)
    'a'[0].upto 'c'[0] do |c|
      old.each do |s|
        ans << c.chr + s
      end
    end
    return ans
  end
end

2.upto(10) do |i|
  a = f(i)
  puts a.join("\n")
end
puts "."