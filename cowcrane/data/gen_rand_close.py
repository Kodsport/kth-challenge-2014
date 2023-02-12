import sys
import random

amplitude, seed = map(int, sys.stdin.readline().split())

random.seed(seed)

m = None
M = None
b = None
B = None

while m == M:
    M = random.randint(-amplitude/10, amplitude/10)
    m = random.randint(-amplitude/10, amplitude/10)

while b == B: 
    B = random.randint(-amplitude/10, amplitude/10)
    b = random.randint(-amplitude/10, amplitude/10)


# go first m, then b
tm_limit = abs(m) + abs(m-M)
tb_limit = tm_limit + abs(M-b) + abs(b-B)

tm = tm_limit
tb = tb_limit 

if random.randint(0,3) == 0:
    tm -= 1

if random.randint(0,3) == 0:
    tb -= 1

if random.randint(0,1) == 0:
    M, B = B, M
    m, b = b, m
    tm, tb = tb, tm

print m, b
print M, B
print tm, tb
