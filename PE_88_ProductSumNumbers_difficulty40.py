# Done on July 2, 2020
# This solves Project Euler problem 88, Product-Sum Number. Difficulty is 40%.
# Given a number k, find the least product-sum number such that a1 + a2 + ... + ak = a1 * a2 * ... * ak
# Obviousy, many of the numbers will be 1s, so need to find the factors greater than 1.
# Note factors don't need to be prime.
# https://projecteuler.net/problem=88

import numpy as np
import csv
from numpy import genfromtxt

# nextint finds the next set of factors to try
def nextint(curr,last):
    lenc = len(curr)
    ii = lenc-1
    incremented=0
    if curr[lenc-1] < last: curr[lenc-1] += 1
    else:
        ii = lenc -1
        while curr[ii]==last and ii>=0: ii -= 1
        if ii >=0:
            curr[ii] += 1
            for jj in range(ii+1, lenc): curr[jj]=curr[ii]
        else:
            curr = [2]*lenc
    return curr

def highest(factors, max_k): #this is the number of factors that are not equal to 1
    return int( (max_k/2**(factors-2))**0.5)+5 #worst-case scenario is factors are all 2s and one or two big numbers
    
max_k=11999 #problem states go up to 12000
combos = [[]]*max_k #this keeps track of the factors which yielded the minimum number for a given k
Nmins = ["inf"]*max_k #this holds those minimum numers


# special case for two non-ones, a and b
print(highest(2,max_k)) # keep track of how large factors have to check
for a in range(2,highest(2,max_k)): 
    for n in range(a**2-2*a,max_k*2,a-1): # n is number of ones; can step by a-1 (key to efficiency)
        b = (a+n)/(a-1) # if a is one factor, then if have n ones we know b is this
        k = n + 2
        P = a*b
        curr=[a,b]
        if k <= len(Nmins)+1:
            if P <= Nmins[k-2]: # if have a new minimum product-sum number for a given k
                Nmins[k-2]=P
                combos[k-2]=curr[:]

#one more special case, for three factors
#what's special is that the third factors increments differently
#logic is very similar to two factor case
print(highest(3,max_k))
for a in range(2,highest(3,max_k)):
    for b in range(a,highest(3,max_k)):
        for n in range(b*(a*b-1)-a-b,max_k*2,a*b-1):
            c = (n+a+b)/(a*b-1)
            k = n + 3
            P = a*b*c
            curr = [a, b, c]
            if k <= len(Nmins)+1:
                if P < Nmins[k-2]:
                    Nmins[k-2]=P
                    combos[k-2]=curr[:]
            
#now can write a loop for all the other numbers of factors
#since the problem says go up to k = 12000, we can stop with 14 factors because 2^14 = 16384
#factors is now really one fewer factor, since we're calculating the last factor, which we call d
#so when factors goes up to 13, that's really a total of 14 factors
for factors in range(3,14): #curr now is one fewer because we are calculating the last factor
    # when this factors is 3, we are calculating the 4th factor
    curr = [2]*factors #we will calculate the last factor
    done = 0 #used to stop the while loop
    lenc = len(curr)
    last = highest(factors+1,max_k)
    print(highest(factors+1,max_k))
    lasttry = [last]*factors
    while not (curr==lasttry and done):
        prod = np.prod(curr)
        sumc = sum(curr)
        for n in range(curr[lenc-1]*(prod-1)-sumc, max_k*2 ,prod-1):
            d = (n+sumc)/(prod-1) #same logic as for 2 or 3 factors, just done curr, an array of factors
            P = prod*d
            k = n + lenc + 1
            thiscurr = curr+[d]
            if k<= len(Nmins)+1:
                if P < Nmins[k-2]:
                    Nmins[k-2]=P
                    combos[k-2]=thiscurr[:]
        curr = nextint(curr,last)
        done = 1

print
print("max(Nmins)",max(Nmins)) #given k=12000, check to see the maximum value as a check on going far enough
print("inf" in Nmins) #check to make sure covered every k
print(sum(set(Nmins))) #calculate number problem is asking for






