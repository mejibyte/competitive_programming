puts 100
for i in (1..1)
for j in (1..10000)
    k = rand(5)
    print "A" unless k != 0;
    print "C" unless k != 1;
    print "G" unless k != 2;
    print "T" unless k != 3;
end
puts ""
end
