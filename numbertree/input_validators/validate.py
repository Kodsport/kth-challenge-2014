#!/usr/bin/env python3
from sys import stdin
import re
import sys

intstr = re.compile("[1-9]\d* [LR]*\n")

line = stdin.readline()
assert intstr.match(line)

a = line.split()
if len(a) == 1:
    a.append("")

h = int(a[0])
assert 1 <= h <= 30
assert len(a[1]) <= h

assert len(stdin.readline()) == 0
sys.exit(42)
