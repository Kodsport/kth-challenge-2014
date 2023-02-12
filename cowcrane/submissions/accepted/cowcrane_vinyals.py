#!/usr/bin/env python3
from sys import stdin
from heapq import heappush, heappop

start = [int(x) for x in stdin.readline().split()]
end = [int(x) for x in stdin.readline().split()]
position = start + end
t = [int(x) for x in stdin.readline().split()]

# cow1, cow2, crane
state = (start[0], start[1], 0)
queue = []
# time, state
heappush(queue, (0, state))
seen = set()

while(queue):
    time, state = heappop(queue)
    if all(state[cow] == end[cow] for cow in range(2)):
        print ("possible")
        exit()
    if state in seen: continue
    seen.add(state)
    crane = state[2]
    for dest in position:
        if dest == crane: continue
        ntime = time + abs(dest - crane)
        if all(ntime <= t[cow] or state[cow] == end[cow] for cow in range(2)):
            heappush(queue, (ntime, (state[0], state[1], dest)))
            if state[0] == state[2]:
                heappush(queue, (ntime, (dest, state[1], dest)))
            if state[1] == state[2]:
                heappush(queue, (ntime, (state[0], dest, dest)))

print ("impossible")
