#!/usr/bin/env python2

from random import randint
from math import floor

modd = 10111. # some prime larger than 10000
modx = 10007. # some prime larger than 10000

d=randint(0,5)+randint(1,modd-1)/modd
x=randint(1, modx-1)/modx
n=10000

print d,n
seps=[]
last = -1
for i in xrange(1,n+1):
    curr = int(floor(d*i-x))
    seps.append(curr-last)
    last=curr
print " ".join(str(x) for x in seps)
