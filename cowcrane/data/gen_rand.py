import sys
import random

amplitude, seed = map(int, sys.stdin.readline().split())

random.seed(seed)

m = None
M = None
b = None
B = None

while m == M:
    M = random.randint(-amplitude/4, amplitude/4)
    m = random.randint(-amplitude/4, amplitude/4)

while b == B: 
    B = random.randint(-amplitude/4, amplitude/4)
    b = random.randint(-amplitude/4, amplitude/4)

tm = random.randint(1, amplitude)
tb = random.randint(1, amplitude)

print m, b
print M, B
print tm,tb
