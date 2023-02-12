#!/usr/bin/env python3

from os import linesep
from sys import stdin,exit
import re

anint = "(0|[1-9]\d*)"
anyints = f"{anint}( {anint})*\n"
ints = re.compile(anyints)

def readints() :
    line = stdin.readline()
    print(line, anyints)
    assert ints.match(line)
    return (int(x) for x in line.split())

def reachable(s,t) :
    seen = [False]*n
    q = [s]
    seen[s] = True
    while q :
        x = q.pop()
        for y in G[x]:
            if y == t : return True
            if seen[y] : continue
            q.append(y)
            seen[y] = True
    return False

n,m = readints()
assert 1 <= n <= 100000
assert 1 <= m <= 100000
G = [[]]*n;
for t in range(m) :
    u,v,w = readints()
    assert 0 <= u < n
    assert 0 <= v < n
    assert 0 < w <= 1000000000
    G[u].append(v);
s,t = readints()
assert 0 <= s < n
assert 0 <= t < n
assert reachable(s,t);

assert len(stdin.readline()) == 0

exit(42)
