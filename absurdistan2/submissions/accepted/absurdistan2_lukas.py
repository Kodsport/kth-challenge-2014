#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Solution by lukasP (Lukáš Poláček)
from sys import stdin
import math

n = int(stdin.readline())
p = [0.0] * (n + 1)
c = [[0] * i + [1] for i in range(n + 1)]

for i in range(n + 1):
    c[i][0] = 1
    for j in range(1, i):
        c[i][j] = c[i - 1][j] + c[i - 1][j - 1]

    p[i] = math.pow(i - 1, i)
    for j in range(2, i - 1):
        p[i] -= math.pow(i - j - 1, i - j) * c[i - 1][j - 1] * p[j]

print("%.9lf" % (p[n] / math.pow(n - 1, n)))
