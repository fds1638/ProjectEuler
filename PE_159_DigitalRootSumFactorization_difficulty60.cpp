// Done 7 July 2020
// Solves Project Eulter problem 159, Digital Root Sum of Factorizations.
// https://projecteuler.net/problem=159
// Difficulty 60%
// A digital root sum of a number: keep addings its digits until you get a number below 10.
// For each number find the max digital root sum of its factorizations.
// Add all those maxima up for numbers less than a million.

// This is sort of a greedy search. For each number, find its prime factorization.
// Multiply together any possibilities of factors whose digital root sums add to 4, 5, or 6,
// because that's the only way to get a digital root sum that is greater.
// Use a hash map to keep track of all the factorizations already tried.

#include <iostream>
#include <array>
#include <math.h>
#include <algorithm>
#include <unordered_map>
#include <iostream>
using namespace std;

// Can use one hash map for all numbers, since no factorization for one number will
// be valid for another number. I experimented with erasing the hashmap, but ultimately 
// the runtime was of the same order of magnitude.
std::unordered_map<std::string, int> themap;

// Function to find the digital root of a number.
int digitalRoot(int n) {
  int runningsum = 0;
  while ( n > 0) {
    runningsum += n%10;
    n = n/10;
  }
  if (runningsum < 10) { return runningsum;}
  else { return digitalRoot(runningsum); }
}

// Function to find the prime factorization of a number.
int primeFactorization(int* fp, int n) {
  int count=0;
  int limit = int(n/2)+1;
  for (int ii=2; ii<limit ; ii++) {
    while ( n%ii==0 ) {
      fp[count]=ii;
      count++;
      n = n/ii;
    }
  }
  for (int ii=count; ii<20 ; ii++) {
    fp[ii]=0;
  }
  return count;
}


// This is the function that does the lion's share of the work.
// Given a number n and its factorization and the length of the factorization
// and the current max of the digital root sum, try to see if you can get
// a larger max by multiplying together some elements. 
// Recursively call itself to multiply further factors together,
// always sorting the new factorization according to size and using
// the hash map to eliminate possibilities already investigated. 
int maxDigRootSum(int* factors, int length, int n, int currmdrs) {
  int mdrs = digitalRoot(n);                                // the drs of the original number
  if (currmdrs > mdrs) { mdrs = currmdrs; }                 // check if have new max
  int allfacdrs = 0;                                        // sum of drs of all factors in curr
  for (int ii=0; ii < length; ii++) {
    allfacdrs += digitalRoot(factors[ii]);
  }
  sort(factors, factors + length);                          // in case factors weren't sort, sort them
  string mapstring = "";                                    // put factors in a csv string
  for (int ii=0; ii < length; ii++) {
    mapstring = mapstring + to_string(factors[ii]) + ",";
  }
  themap[mapstring]=1;                                      // put string in hash map
  if (allfacdrs > mdrs) { mdrs = allfacdrs; }               // check if new factorization is a new max
  for (int ii=0; ii < length-1 ; ii++) {                    // loop through current factorization...
    for (int jj=ii+1; jj < length ; jj++) {
      if (digitalRoot(factors[ii])+digitalRoot(factors[jj]) >= 4 && digitalRoot(factors[ii])+digitalRoot(factors[jj])<= 6 ) {
        int newfactors[length-1];
        for (int kk=0; kk<ii; kk++){
          newfactors[kk]=factors[kk];                       // ... copy all factors ...
        }
        newfactors[ii]=factors[ii]*factors[jj];             // ... except the two being multiplied together ...
        for (int kk=ii+1; kk<jj; kk++){
          newfactors[kk]=factors[kk];                       // ... continue copying ...
        }
        for (int kk=jj+1; kk<length; kk++){
          newfactors[kk-1]=factors[kk];                     // ... finish copying.
        }
        sort(newfactors, newfactors + length-1);            // sort
        string newstring = "";                              // put sorted newfactors into string ...
        for (int mm=0; mm < length-1; mm++) {
          newstring = newstring + to_string(newfactors[mm]) + ",";
        }
        if (themap.find(newstring)==themap.end()) {         // If sorted newfactors haven't been tried yet ... 
          allfacdrs = maxDigRootSum(newfactors, length-1, n, mdrs);  // ... call maxDigRootSum recursively.
        } 
        if (allfacdrs > mdrs) { mdrs = allfacdrs; }         // Check for a new max.
      }
    }
  }  
  return mdrs;
}

int main()
{
  int currnum[20];  // problem asks to go up to 1 million, which is less than 2^20
  int numfacs;      // number of factors in factorization
  int currmdrs;     // current max of digital root sum for each number


  int summdrs = 0;  // running sum of maxima
  for (int nn=2; nn<1000000; nn++) {
    numfacs = primeFactorization(currnum, nn);                      // get factorization
    currmdrs = maxDigRootSum(currnum, numfacs, nn, 0);              // find max dig root sum
    // can keep track of progress if you're willing to slow it down
    //std::cout << "nn " << nn << " currmdrs " << currmdrs << "\n";
    summdrs += currmdrs;                                            // add to running total
    themap.erase(themap.begin(), themap.end());                     // can erase hash map (not necessary)
  }
  std::cout << "summdrs " << summdrs << "\n";                       // print final sum




}

