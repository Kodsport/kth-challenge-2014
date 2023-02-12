#!/usr/bin/python
from sys import stdin
import re
import sys

oneint = re.compile("[1-9]\d*\n")

line = stdin.readline()
assert oneint.match(line)
n = int(line)
assert 2 <= n <= 140

assert len(stdin.readline()) == 0
sys.exit(42)
