def count(s)
  n = s[0..-2].to_i
  type = s[-1..-1].upcase
  if type == "H"
    return 1.upto(n).inject(0) { |s, k| s + k * k }
  else
    return 1.upto(n).select { |e| e % 2 == n % 2 }.inject(0) { |s, k| s + k * k }
  end
end