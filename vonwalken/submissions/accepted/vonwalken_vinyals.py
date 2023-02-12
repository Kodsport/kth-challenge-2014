#!/usr/bin/env python3
from sys import stdin

d = float(stdin.readline().split()[0])
c = (int(x) for x in stdin.readline().split())
lowerbound=0.
upperbound=1.
pole=0.
steps=0
# The starting point x satisfies
# 0 < x < 1 and
# x + steps_i -1 < i * D < x + steps_i
for ci in c:
    steps=steps+ci
    pole=pole+d
    lowerbound=max(lowerbound,pole-steps)
    upperbound=min(upperbound,pole-(steps-1))
    if (lowerbound>upperbound):
        print("impossible")
        break
else:
    print("possible")

