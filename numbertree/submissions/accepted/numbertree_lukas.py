#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#Solution by lukasP (Lukáš Poláček)
from sys import stdin
from functools import reduce

a = stdin.readline().split()
h = int(a[0])
s = a[1] if len(a) > 1 else ""

print(2 ** (h + 1) - reduce(lambda x, y: x * 2 + (y == 'R'), s, 1))
