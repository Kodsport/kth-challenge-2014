#!/usr/bin/env python3
import sys
from math import sqrt
from math import floor
D = int(sys.stdin.readline())

n2 = 1
while True:
    if n2*n2 - (n2-1)*(n2-1) > D:
        break
    if n2**2 >= D:
        n1 = sqrt(n2**2 - D)
        if int(floor(n1 - 1e-7)) != int(floor(n1)):
            print(int(floor((n1))), int(floor(n2)))
            sys.exit()
    n2 += 1

print("impossible")
