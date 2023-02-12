#!/usr/bin/env python3
from sys import stdin

d = float(stdin.readline().split()[0])
c = [int(x) for x in stdin.readline().split()]
n = len(c)
s = sum(c)
if abs(d*n-s)<1:
    print("possible")
else:
    print("impossible")
