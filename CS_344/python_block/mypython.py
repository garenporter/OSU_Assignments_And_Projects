import random
import string

random.seed()
    
file1 = open("Durator", "w")
file2 = open("Western Plaguelands", "w")
file3 = open("Thunderbluff", "w")

for i in range(3):
    line=''.join(random.choice(string.ascii_lowercase) for j in range(10))
    print line
    file1.write("%s\n" % (line))
    file2.write("%s\n" % (line))
    file3.write("%s\n" % (line))

a = random.randint(1,43)
b = random.randint(1,43)

print("%s\n%s\n%s" % (a, b, a*b))