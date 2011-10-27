import random

x = []
y = []

random.seed()

for j in range(0, 1000):

    x = []
    y = []
    while (len(x) < 3):
        a = random.randint(-1000, 1000)
        esta = False
        for i in range(0, len(x)):
            if x[i] == a:
                esta = True
        if not esta:
            x.append(a)

    while (len(y) < 3):
        a = random.randint(-1000, 1000)
        esta = False
        for i in range(0, len(y)):
            if y[i] == a:
                esta = True
        if not esta:
            y.append(a)

        

    s = str(x[0]) + " " + str(y[0]) + " " + str(x[1]) + " " + str(y[1]) + " " + str(x[2]) + " " + str(y[2]);
    print s

print "0 0 0 0 0 0"
