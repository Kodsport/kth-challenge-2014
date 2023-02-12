#!/usr/bin/env python3
from sys import stdin
from math import *

N = int(stdin.readline())
x = [0 for a in range(N)]
y = [0 for a in range(N)]
r = [0 for a in range(N)]
for i in range(N):
	x[i], y[i], r[i] = map(float,stdin.readline().split())
events = []
for i in range(len(x)):
	for j in range(i):
		dx = x[i]-x[j];
		dy = y[i]-y[j];
		a = atan2(dy,dx);
		if a < 0:
			a += pi
		b = asin((r[i]+r[j])/sqrt(dx**2+dy**2))
		start = a-b
		end = a+b
		events.append((start,True))
		events.append((end,False))
		if (start < 0):
			events.append((start+pi,True))
			events.append((end+pi,False))
		if (end > pi):
			events.append((start-pi,True))
			events.append((end-pi,False))
best = 0
depth = 0
events.sort()
events.append((events[0][0]+pi,True))
for i in range(len(events)):
	if events[i][1]:
		depth += 1
	else:
		depth -= 1
		if depth == 0:
			best = max(best,events[i+1][0]-events[i][0])
print('{:.9f}'.format(best))
