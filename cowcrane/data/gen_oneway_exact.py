import sys
import random

amplitude, seed = map(int, sys.stdin.readline().split())

random.seed(seed)


# start - startin - endin - end

m = None
M = None
b = None
B = None

start = random.randint(1, amplitude/10)
end = random.randint(start+1, amplitude/10)

startin = random.randint(start+1, end) 
endin = random.randint(startin+1, end) 

m = start
M = end

b = startin
B = endin

tm = endin + endin - startin + end - startin
tb = endin

if random.randint(0,1) == 0:
    m, b = b, m
    M, B = B, M
    tm, tb = tb, tm

if random.randint(0,1) == 0:
    m, b, M, B = -m, -b, -M, -B

print m, b
print M, B
print tm,tb
