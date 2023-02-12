#!/usr/bin/env python3
from sys import stdin
import re
import sys

integer = "(0|-?[1-9]\d*)"
floating = integer + "?(\.\d{1,12})?"
manyint = re.compile("(" + integer + " )*" + integer + "\n")

line = stdin.readline()
assert re.match(floating + " " + integer + "\n", line)
d,n = line.split()
d = float(d)
n = int(n)
assert 2 <= d <= 3
assert 0 <= n <= 10000

line = stdin.readline()
assert manyint.match(line)
c = [int(i) for i in line.split()]
assert len(c) == n
for ci in c:
    assert 2 <= ci <= 3

assert len(stdin.readline()) == 0
sys.exit(42)
