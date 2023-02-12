# Solution by Ulf Lundstrom
from sys import stdin

D = float(stdin.readline().split()[0])
c = list(map(int,stdin.readline().split()))
a, b = 0, 1
steps = 0
for i in range(len(c)):
	steps += c[i]
	b = min(b,(i+1)*D-steps+1)
	a = max(a,(i+1)*D-steps)
if a <= b:
	print('possible')
else:
	print('impossible')
