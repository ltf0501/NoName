import random
print("300000 300000")
for i in range(300000):
    print(random.randint(1, 1000))
for i in range(300000):
    a, b = random.randint(1, 300000), random.randint(1, 300000)
    while a == b: b = random.randint(1, 300000)
    print(a + 1, b + 1, max(560, i - 100 * random.randint(1, 1000)))
