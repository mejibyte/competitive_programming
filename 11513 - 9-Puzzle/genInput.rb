def permute_array(a)
  1.upto(a.length - 1) do |i|
    j = rand(i + 1)
    a[i], a[j] = a[j], a[i]
  end
  a
end

for i in (1..1000) do
r = permute_array [1, 2, 3, 4, 5, 6, 7, 8, 9]
s = "#{r[0]} #{r[1]} #{r[2]}\n#{r[3]} #{r[4]} #{r[5]}\n#{r[6]} #{r[7]} #{r[8]}\n"
puts s
puts ""
end