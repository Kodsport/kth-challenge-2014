#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Solution by lukasP (Lukáš Poláček)
from sys import stdin, exit

d = int(stdin.readline())

for i in range(0, 200000):
    si = i * i
    for j in range(i + 1, 200000):
        sj = j * j
        if sj - si > d:
            break
        if sj - si == d:
            print("{0} {1}".format(i, j))
            exit(0)

print("impossible")
