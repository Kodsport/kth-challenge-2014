from math import *
import random

def solve(x,y,r):
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
	print best
	return best

def testcase(x,y,r,ans=None):
	r8 = lambda x: round(x,8)
	x = map(r8,x)
	y = map(r8,y)
	r = map(r8,r)
	global n
	f = open('secret/tomosynthesis-{:02d}.in'.format(n),'w')
	f.write(str(len(x))+'\n')
	for i in range(len(x)):
		f.write('{:.8f} {:.8f} {:.8f}\n'.format(x[i],y[i],r[i]))
	f.close();
	ans2 = solve(x,y,r)
	if ans != None:
		if abs(ans2-ans) > 1e-8:
			print 'Error in testcase ', n, '. Solver gives', ans2,
			print 'but it should be ', ans
	f = open('secret/tomosynthesis-{:02d}.ans'.format(n),'w')
	f.write('{:.9f}\n'.format(ans2))
	f.close()
	n = n+1

global n
n = 1;
testcase([-1, 1, 0],[-1, -1, 1],[.999999, .999999, .1],0)
testcase([-1, 1, 0],[-1, -1, 1],[1e-6, 1e-6, 1e-6],
	-atan(.5)+pi/2-2e-6/sqrt(5)-1e-6)
testcase([-1, 1],[0, 0],[1/sqrt(2), 1/sqrt(2)],pi/2)
testcase([0, 1], [0, 1], [0.5, 0.5],pi/2)
testcase([0, -10], [0, 10], [0.5, 0.5])
testcase([0, 10.5], [0, -10.5], [0.5, 0.5])
testcase([0, -999.99], [0, -999.99], [0.5, 0.5])
testcase([-1000, 1000], [0, 0], [1e-3, 1e-3],pi-2e-6)
testcase([1000, -0.1, 0],[0, 0, 2],[1000, .001, .001])
testcase([1000, -0.1, 1],[0, 0, 50],[1000, .001, .001])
testcase([10*x for x in range(100)], [0 for x in range(100)],
	[1+x/100 for x in range(98)]+[2,2],pi-2*asin(2./5))
random.seed(1);
testcase([random.random()*2000-1000 for x in range(5)],
	[random.random()*2000-1000 for x in range(5)], [1.234 for x in range(5)])
testcase([random.random()*2000-1000 for x in range(100)],
	[random.random()*2000-1000 for x in range(100)], [1 for x in range(100)])
testcase([random.random()*2000-1000 for x in range(100)],
	[random.random()*2000-1000 for x in range(100)], [1e-6 for x in range(100)])
testcase([random.random()*2000-1000 for x in range(100)],
	[random.random()*2000-1000 for x in range(100)],
	[random.random() for x in range(100)])
testcase([cos(x*2*pi/20) for x in range(20)],
	[sin(x*2*pi/20) for x in range(20)],
	[0.02 for x in range(20)])
testcase([cos(x*2*pi/20) for x in range(20)],
	[sin(x*2*pi/20) for x in range(20)],
	[0.01 for x in range(20)])