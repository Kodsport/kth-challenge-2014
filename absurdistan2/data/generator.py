#!/usr/bin/env python3
import random
import sys
from sys import stdin


s = stdin.readline().strip().split()
if s[0] == "exactly":
    n = int(s[1])
else:
    n = random.randint(int(s[1]), int(s[2]))

print(n)
