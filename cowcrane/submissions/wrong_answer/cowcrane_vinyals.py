#!/usr/bin/env python3
from sys import stdin

m,b = (int(x) for x in stdin.readline().split())
M,B = (int(x) for x in stdin.readline().split())
tm,tb = (int(x) for x in stdin.readline().split())

# Try moving Monica first
tmm = abs(m) + abs(M-m)
tbb = tmm + abs(M-b) + abs(B-b)

if (tmm <= tm and tbb <= tb) :
    print("possible")
    exit()

# Try moving Bob first
tbb = abs(b) + abs(B-b)
tmm = tbb + abs(B-m) + abs(M-m)

if (tmm <= tm and tbb <= tb) :
    print ("possible")
else:
    print ("impossible")
