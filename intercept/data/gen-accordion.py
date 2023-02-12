#!/usr/bin/env python2

N=60000
MX=1000000000

print N+1,4*N/3

for x in xrange(0,N,3):
    print x,x+1,MX
    print x,x+2,MX
    print x+1,x+3,MX
    print x+2,x+3,MX

print 0,N

