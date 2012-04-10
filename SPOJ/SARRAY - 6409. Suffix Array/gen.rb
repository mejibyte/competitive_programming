n = 65
from = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789".split("")
n.times do
  #print (rand(0x7E - 0x20 - 1) + 0x20).chr
  print 'a'
end
puts