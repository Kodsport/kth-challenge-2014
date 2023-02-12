#!/usr/bin/python
from sys import stdin
import re, sys

line = stdin.readline()
assert re.match("[1-9]\d*\n", line)
D = int(line)
assert 1 <= D <= 200000

assert len(stdin.readline()) == 0
sys.exit(42)
