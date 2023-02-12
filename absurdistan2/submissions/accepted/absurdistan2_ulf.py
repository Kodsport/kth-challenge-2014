#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Solution by Ulf Lundström
from sys import stdin

N = int(stdin.readline())

A = [[0. for i in range(N+1)] for j in range(N+1)]
A[0][0] = 1.

for i in range(N):
	A[i+1][0] = A[i][0]*(N-i-1)/(N-1)
	A[i][1] = A[i][0]*i/(N-1)
	for j in range(1,N):
		A[i-j][j+1] = A[i-j][j]*(N-i-1)/(N-1)
		A[i][1] += A[i-j][j]*(i-j+1)/(N-1)
print('{:.9f}'.format(A[N-1][1]))
