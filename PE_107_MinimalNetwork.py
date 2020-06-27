# Done Jun 26 2020
# Project Euler problem 107 difficulty 35%
# Given a graph represented by an n by n matrix, 
# where the entries represent the weights of the edges (symmetrix matrix),
# find the spanning tree with minimum weight.
# The problem gives a 40 by 40 matrix, ie 40 nodes, ie 39 edges in spanning tree.
# This is my implementation of Prim's algorithm.
import numpy as np
import csv
from numpy import genfromtxt

# Get the matrix giving current graph.
# Note that lack of edges is given by entries of a dash ("-").
# In the code I change those to -1 so that it's numerical.
#P = genfromtxt('network_107_practice.csv',delimiter=',',dtype=int)
P = genfromtxt('p107_network.txt',delimiter=',',dtype=int)

numnodes = len(P) #number of nodes in the graph

# Try starting from every possible node and see if I get the same answer. I do.
for currowinit in range(numnodes):
    choices = [] #keep track of current options for next edge to add
    visited = [] # array with all nodes already added
    initcost = sum(sum(np.where(P<0,0,P)))/2 #find initial cost
    spancost = 0 #start final treespan cost as zero
    currowidx = currowinit #start with row 0, as good a row as any
    visited.append(currowidx) #add starting node to visited nodes
    currow = np.where(P[currowidx]>0,P[currowidx],10000) #make cost of nonexisting edges 10000
    choices.append(currow) #add edges emanating from initial node to list of possibles
    for ii in range(numnodes-1):
        minidx = np.argmin(choices) #find the argument of the minimum edge leaving current state
        minrow = minidx/numnodes # find the row coordinate
        mincol = minidx%numnodes # find the col coordinate

        #add the current minimal cost to the spancost
        spancost += choices[minrow][mincol]

        #since we've chosen the next edge to add, remove the possibility of
        #going to that node again
        for jj in range(ii+1):
            choices[jj][mincol]=10000

        # since we've chosen a new vertex, add all the edges
        # emanating from that vertex to our possibilities
        currow = np.where(P[mincol]>0,P[mincol],10000) #make cost of nonexisting edges 10000, 

        # remove all connections from the new vertex to already-visited vertices
        for kk in range(len(visited)):
            currow[visited[kk]]=10000

        # append the list of new possible edges to the others
        choices.append(currow)

        #update variable for current vertex and append to visited
        currowidx = mincol
        visited.append(currowidx)

    #check I get the same answer no matter where I start
    print("init",currowinit,"initcost-spancost",initcost-spancost)

