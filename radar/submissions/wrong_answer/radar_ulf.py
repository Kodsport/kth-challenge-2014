#!/usr/bin/env python3
# Solution by Ulf Lundstrom
from sys import stdin

def euclid(a,b):
	if b:
		d,y,x = euclid(b,a%b)
		return d, x, y-a//b*x
	return a, 1, 0

def chinese(a,m,b,n):
	d,x,y = euclid(m,n)
	return (a*y%m*n + b*x%n*m)%(m*n)
	# ret = a*(y+m)%m*n + b*(x+n)%n*m;
	# if ret > m*n:
	# 	ret -= m*n
	# return ret
def chinese3(a,m,b,n,c,o):
	return chinese(chinese(a,m,b,n), m*n, c, o)

m1,m2,m3 = map(int,stdin.readline().split())
x1,x2,x3 = map(int,stdin.readline().split())
y1,y2,y3 = map(int,stdin.readline().split())

best = m1*m2*m3
for d1 in range(-y1,y1+1):
	for d2 in range(-y2,y2+1):
		for d3 in range(-y3,y3+1):
			if (d1 > -y1 and d2 > -y2 and d3 > -y3):
				break
			best = min(best,chinese3((x1+d1)%m1,m1, (x2+d2)%m2,m2,
				(x3+d3)%m3,m3))
print(best)
