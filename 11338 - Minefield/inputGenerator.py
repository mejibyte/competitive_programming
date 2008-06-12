import random

for j in range(0, 10):
    print "20 20"
    print "500"
    for i in range(0, 500):
        s = str(random.randint(0, 19)) + "." + str(random.randint(0,9)) + str(random.randint(0,9))
        s = s + " "
        s = s + str(random.randint(0, 19)) + "." + str(random.randint(0,9)) + str(random.randint(0,9))
        print s
        
    print str(random.randint(30, 40))+".00"

print "*"
