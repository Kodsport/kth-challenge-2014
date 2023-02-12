#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Solution by Ulf Lundström
from sys import stdin

x = stdin.readline().split()
H = int(x[0])
S = x[1] if len(x) > 1 else ""
r = 0
for a in S:
	r = r*2 + (a=='R')
print(2**(H+1) - 2**len(S) - r)
