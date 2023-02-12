#!/usr/bin/env python3
from sys import stdin
import re
import sys

integer = "(-?0|-?[1-9]\d*)"
floating = integer + "(\.\d{1,8})?"
eps = 1e-8;

line = stdin.readline()
assert re.match(integer + "\n", line)
N = int(line)
assert 2 <= N <= 100
X = []
Y = []
R = []

for i in range(N):
	line = stdin.readline()
	assert re.match(floating + " " + floating + " " + floating + "\n",line)
	x, y, r = line.split()
	x = float(x)
	y = float(y)
	r = float(r)
	assert -1000 <= x <= 1000
	assert -1000 <= y <= 1000
	assert 0 < r <= 1000
	for j in range(i-1):
		assert (X[j]-x)**2 + (Y[j]-y)**2 > (R[j] + r)**2 + eps
	X.append(x)
	Y.append(y)
	R.append(r)


assert len(stdin.readline()) == 0
sys.exit(42)
