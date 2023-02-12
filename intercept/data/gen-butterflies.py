#!/usr/bin/env python2

from random import random
#import networkx as nx
#import matplotlib.pyplot as plt

layers=3
width=2**3
order=layers*width
size=order*2

blocks=100000/size
totalorder=blocks*order+width
totalsize=blocks*size

expect_shortcuts=2.
prob_shortcut=expect_shortcuts/size

print totalorder,totalsize

#G = nx.DiGraph()

for butterfly in range(blocks):
    for layer in range(layers):
        for vertex in range(width):
            u = butterfly*order + layer*width + vertex
            for jump in range(2):
                v = u + width - vertex + (vertex + jump*(2**layer))%width
                weight = 50 if random()<prob_shortcut else 100
#                weight = 50 if u%13==1 else 100
                print u,v,weight
#                G.add_edge(u,v)

print 0,totalorder-1

#nx.draw(G,pos=nx.graphviz_layout(G,prog='dot'))
#plt.show()
