#!/usr/bin/env python3
from sys import stdin

EPS=1e-7

d = float(stdin.readline().split()[0])
c = (int(x) for x in stdin.readline().split())
lowerbound=0.
upperbound=1.
pole=0.
steps=0
for ci in c:
    steps=steps+ci
    pole=pole+d
    lowerbound=max(lowerbound,pole-steps)
    upperbound=min(upperbound,pole-(steps-1))
    assert abs(lowerbound-upperbound) > 2 * EPS # two times just to be sure

exit(42)
