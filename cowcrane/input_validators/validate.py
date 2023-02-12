#!/usr/bin/env python3
from sys import stdin
import re
import sys

twoints = re.compile("(0|-?[1-9]\d*) (0|-?[1-9]\d*)\n")

line = stdin.readline()
assert twoints.match(line)
m, b = map(int, line.split())

assert -10**8 <= m <= 10**8
assert -10**8 <= b <= 10**8

line = stdin.readline()
assert twoints.match(line)
M, B = map(int, line.split())

assert -10**8 <= M <= 10**8
assert -10**8 <= B <= 10**8

assert m != M
assert b != B

line = stdin.readline()
assert twoints.match(line)
tm, tb = map(int, line.split())

assert 1 <= tm <= 10**8
assert 1 <= tb <= 10**8

assert len(stdin.readline()) == 0
sys.exit(42)
