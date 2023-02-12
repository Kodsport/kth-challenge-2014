#!/usr/bin/python
from sys import stdin
import re
import sys


def isprime(x):
    d = 2
    while d * d <= x:
        if x % d == 0:
            return False
        d += 1
    return True

integer = "(0|[1-9]\d*)"
threeint = re.compile("(" + integer + " ){2}" + integer + "\n")

line = stdin.readline()
assert threeint.match(line)
m = list(map(int, line.split()))
for x in m:
    assert 0 < x <= 10 ** 6
    assert isprime(x)

for i in range(3):
    for j in range(i):
        assert m[i] != m[j]

line = stdin.readline()
assert threeint.match(line)
x = list(map(int, line.split()))
for i in range(3):
    assert 0 <= x[i] < m[i]

line = stdin.readline()
assert threeint.match(line)
y = list(map(int, line.split()))
for q in y:
    assert 0 <= q <= 300

assert len(stdin.readline()) == 0
sys.exit(42)
