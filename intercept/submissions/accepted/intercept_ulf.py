#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Solution by Ulf Lundström
from sys import stdin
from queue import PriorityQueue


N,M = map(int,stdin.readline().split())
G = [[] for i in range(N)]
for i in range(M):
	u,v,w = map(int,stdin.readline().split())
	G[u].append((v,w))
	G[v].append((u,w))
s,t = map(int,stdin.readline().split())

D = [float('inf') for i in range(N)]
Q = PriorityQueue()
P = [[] for i in range(N)]
D[s] = 0;
Q.put((0,s))
while not Q.empty():
	p, n = Q.get()
	for to, w in G[n]:
		if p + w < D[to]:
			D[to] = p+w
			Q.put((p+w,to))
			P[to] = [(n,w)]
		elif p + w == D[to]:
			P[to].append((n,w))

D = [float('inf') for i in range(N)]
Q.put((0,t))
res = []
while not Q.empty():
	p, n = Q.get()
	if Q.empty():
		res.append(n)
	for to, w in P[n]:
		if p + w < D[to]:
			D[to] = p+w
			Q.put((p+w,to))
for r in sorted(res):
	print(r)
