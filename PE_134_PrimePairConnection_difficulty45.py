# Done on July 3 2020
# This solves Project Euler problem 134, Prime Pair Connection. Difficulty is 45%.
# Given two consecutive primes, p1 and p2, where p1 < p2, find a number n
# such that (1) the last digits of n are the digits of p1, 
# and (2) n is divisble by p2.
# The idea is to use long multiplication. You know you have some factor times p2,
# and you find digit by digit of the factor starting at the ones place and working
# to tens, then hundreds, etc.
# https://projecteuler.net/problem=88

import numpy as np
import csv
from numpy import genfromtxt

def isPrime(n): #is a number prime?
    if n<=2: return False
    lim = int(n**0.5)+1
    #print(lim)
    for ii in range(2,lim):
        #print n%ii
        if n%ii==0: return False
    return True

def primeFactorization(n): #prime factorization of a number
    n0 = n
    lim = n/2+1
    if n < 2: return []
    pf = []
    while n%2==0:
        pf.append(2)
        n = n/2
    for ii in range(3,lim):
        while n%ii==0:
            pf.append(ii)
            n = n/ii
    if n0==n: pf.append(n0)
    return pf

def numDigits(n): #gives number digits in a number
    count = 0
    while n > 0:
        n = n/10
        count += 1
    return count

def getDig(n,i): # given n, get digit i. If i=1 ones, if i=2 tens, etc.
    return (n%(10**(i)))/(10**(i-1))

def digToFrom(n): #enter 1,3,7,9 get 0,1,2,3; gives row indices for multby
    if n==1: return 0
    if n==3: return 1
    if n==7: return 2
    if n==9: return 3

def digToTo(n): # gives col indices for multby
    return n

# since we are multiplying by a prime, we know the larger prime ends in 1, 3, 7, or 9
# the four rows of multby represent those four number
# the ten columns represent 0 through 9
# so if you have a 3 and you want to multiply it by something so that the product ends it 2,
# you look at entry [1][2] in the table (because row index 1 represents number 3)
# you get a 4, because 3*4 = 12 which ends in 2
multby = [
    [0,1,2,3,4,5,6,7,8,9],
    [0,7,4,1,8,5,2,9,6,3],
    [0,3,6,9,2,5,8,1,4,7],
    [0,9,8,7,6,5,4,3,2,1]]


counter = 0 #this is the sum we're keeping track of
lo = 5
hi = 7
while lo < 1000000: # only want lower prime less than a million per directions
    # essentially do long multiplication
    # You know you'll take the hi prime, multiply it by some factor,
    # and the last digits of the product will be the lo prime.
    # You automatically know the last digit of the factor, so start there
    # and work your way forward.
    # Keep track of what you have so far using the variable sofar.
    lenf = numDigits(lo)
    factor = ["inf"]*lenf
    sofar = 0
    for ii in range(lenf):
        factor[lenf-(ii+1)] = multby[digToFrom(getDig(hi,1))][digToTo((getDig(lo,ii+1)-getDig(sofar*hi,ii+1))%10)]
        sofar = sofar + factor[lenf-(ii+1)]*10**((ii+1)-1)
    #print (lo, hi, hi*sofar)  # if you want to check your work
    counter += hi*sofar
    lo = hi
    jj = hi+1
    while not isPrime(jj):
        jj += 1
    hi = jj
       
print
print("sum", counter)
