import random

for i in range(0, 5606):
    j = random.randint(1, 10000)
    print str(j) + " " + str(random.randint(j+1, 10001))
