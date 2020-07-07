// Done July 5 2020
// Solves Project Euler problem 128, Hexagonal Tile Differences
// https://projecteuler.net/problem=128
// Difficulty 55%
// The problem looks at hexagons tiling a plane, with the hexagons numbered starting at 1
// and spiraling out from that first hexagon. For each hexagon, find the six numbers that
// are the differences between the hexagon's number and the numbers of the neighboring hexagons.
// Find all those hexagons which have 3 prime numbers among those six differences.
// What is the 2000th hexagon with 3 prime numbers?

// Initially I didn't realize that all hexagons with three primes had to be either the first
// or the last in a ring. So most of the program was written with the idea of finding a pattern
// and calculating how the number of prime differences for each hexagon. I left most of that 
// work in here, even though the main part of the program doesn't use it.

#include <iostream>
#include <array>
#include <math.h>

// Given a hexagon number in the pattern specified by the problem,
// return the ring that it is in. Hexagon 1 is ring 0, hexagons 2 through 7 are ring 1, etc.
long ring (long hexagon)
{
  // Given a hexagon number, return the number of the ring
  // it is in. Hexagon 1 is ring 0, hexagons 2 through 7 are ring 1, etc.
  if ( hexagon == 1) { return 0;}
  else 
  { long r = 0;
    long increment = 6;
    long curlim = 1;
    while ( hexagon > curlim) {
      curlim += increment;
      increment += 6;
      r++;
    }
    return r;
  }
}

char letter (long hexagon)
{
  // Given a hexagon number, return the letter code of its location in its ring.
  // A = top,  B = top left side,  C = top left corner, D = left side,
  // E = bottom left corner, F = bottom left side, G = bottom,
  // H = bottom right side, I = bottom right corner, J = right side
  // K = top right corner, L = top right side, M = last hex next to A 
  // Only hexagons A and M end up being relevant.
  if ( hexagon == 1) { return 'Z';}
  else 
  { long r = 0;
    long increment = 6;
    long curlim = 1;
    long lower, diff;
    while ( hexagon > curlim) {
      curlim += increment;
      increment += 6;
      r++;
    }
    increment -= 6;
    lower = curlim - increment + 1;
    //std::cout << hexagon <<  " curlim " << curlim << " lower " <<  lower << " inc " << increment <<  "\n";
    diff = hexagon - lower;
    if (diff == 0) { return 'A';}
    else if ( diff < increment/6 ) { return 'B';}
    else if ( diff == increment/6 ) { return 'C';}
    else if ( diff < increment/3 ) { return 'D';}
    else if ( diff == increment/3 ) { return 'E';}
    else if ( diff < increment/2 ) { return 'F';}
    else if ( diff == increment/2 ) { return 'G';}
    else if ( diff < 2*increment/3 ) { return 'H';}
    else if ( diff == 2*increment/3 ) { return 'I';}
    else if ( diff < 5*increment/6 ) { return 'J';}
    else if ( diff == 5*increment/6 ) { return 'K';}
    else if ( diff < increment-1 ) { return 'L';}
    else if ( diff == increment-1 ) { return 'M';}
    else {return 'Y';}
  }
}

void startertable(long* current, long hex) {
  // Enter the differences for the first 37 hexagons, ie rings 0, 1, and 2, 
  // until the pattern establishes itself.
  // The pattern establishes itself more quickly if you only consider hexagons A and M.
  switch(hex){
    case 1:
      current[0]=1;current[1]=2;current[2]=3;current[3]=4;current[4]=5;current[5]=6;
      break;
    case 2:
      current[0]=6;current[1]=7;current[2]=1;current[3]=1;current[4]=5;current[5]=17;
      break;
    case 3:
      current[0]=6;current[1]=7;current[2]=8;current[3]=1;current[4]=2;current[5]=1;
      break;
    case 4:
      current[0]=1;current[1]=7;current[2]=8;current[3]=9;current[4]=1;current[5]=3;
      break;
    case 5:
      current[0]=4;current[1]=1;current[2]=8;current[3]=9;current[4]=10;current[5]=1;
      break;
    case 6:
      current[0]=1;current[1]=5;current[2]=1;current[3]=9;current[4]=10;current[5]=11;
      break;
    case 7:
      current[0]=12;current[1]=5;current[2]=6;current[3]=1;current[4]=10;current[5]=11;
      break;
    case 8:
      current[0]=12;current[1]=13;current[2]=1;current[3]=6;current[4]=11;current[5]=29;
      break;
    case 9:
      current[0]=12;current[1]=13;current[2]=1;current[3]=6;current[4]=7;current[5]=1;
      break;
    case 10:
      current[0]=12;current[1]=13;current[2]=14;current[3]=1;current[4]=7;current[5]=1;
      break;
    case 11:
      current[0]=1;current[1]=13;current[2]=14;current[3]=1;current[4]=7;current[5]=8;
      break;
    case 12:
      current[0]=1;current[1]=13;current[2]=14;current[3]=15;current[4]=1;current[5]=8;
      break;
    case 13:
      current[0]=9;current[1]=1;current[2]=14;current[3]=15;current[4]=1;current[5]=8;
      break;
    case 14:
      current[0]=9;current[1]=1;current[2]=14;current[3]=15;current[4]=16;current[5]=1;
      break;
    case 15:
      current[0]=9;current[1]=10;current[2]=1;current[3]=15;current[4]=16;current[5]=1;
      break;
    case 16:
      current[0]=1;current[1]=10;current[2]=1;current[3]=15;current[4]=16;current[5]=17;
      break;
    case 17:
      current[0]=1;current[1]=10;current[2]=11;current[3]=1;current[4]=16;current[5]=17;
      break;
    case 18:
      current[0]=18;current[1]=1;current[2]=11;current[3]=1;current[4]=16;current[5]=17;
      break;
    case 19:
      current[0]=18;current[1]=11;current[2]=17;current[3]=12;current[4]=1;current[5]=17;
      break;
    case 20:
      current[0]=18;current[1]=19;current[2]=1;current[3]=12;current[4]=17;current[5]=41;
      break;
    case 21:
      current[0]=18;current[1]=19;current[2]=1;current[3]=12;current[4]=13;current[5]=1;
      break;
    case 22:
      current[0]=18;current[1]=19;current[2]=1;current[3]=12;current[4]=13;current[5]=1;
      break;
    case 23:
      current[0]=18;current[1]=19;current[2]=20;current[3]=1;current[4]=13;current[5]=1;
      break;
    case 24:
      current[0]=1;current[1]=19;current[2]=20;current[3]=1;current[4]=13;current[5]=14;
      break;
    case 25:
      current[0]=1;current[1]=19;current[2]=20;current[3]=1;current[4]=13;current[5]=14;
      break;
    case 26:
      current[0]=1;current[1]=19;current[2]=20;current[3]=21;current[4]=1;current[5]=14;
      break;
    case 27:
      current[0]=15;current[1]=1;current[2]=20;current[3]=21;current[4]=1;current[5]=14;
      break;
    case 28:
      current[0]=15;current[1]=1;current[2]=20;current[3]=21;current[4]=1;current[5]=14;
      break;
    case 29:
      current[0]=15;current[1]=1;current[2]=20;current[3]=21;current[4]=22;current[5]=1;
      break;
    case 30:
      current[0]=15;current[1]=16;current[2]=1;current[3]=21;current[4]=22;current[5]=1;
      break;
    case 31:
      current[0]=15;current[1]=16;current[2]=1;current[3]=21;current[4]=22;current[5]=1;
      break;
    case 32:
      current[0]=1;current[1]=16;current[2]=1;current[3]=21;current[4]=22;current[5]=23;
      break;
    case 33:
      current[0]=1;current[1]=16;current[2]=17;current[3]=1;current[4]=22;current[5]=23;
      break;
    case 34:
      current[0]=1;current[1]=16;current[2]=17;current[3]=1;current[4]=22;current[5]=23;
      break;
    case 35:
      current[0]=24;current[1]=1;current[2]=17;current[3]=1;current[4]=22;current[5]=23;
      break;
    case 36:
      current[0]=24;current[1]=1;current[2]=17;current[3]=18;current[4]=1;current[5]=23;
      break;
    case 37:
      current[0]=24;current[1]=17;current[2]=29;current[3]=18;current[4]=1;current[5]=23;
      break;
    default:
      current[0]= -1;
  }
}

// Is a given number a prime?
bool isPrime(long n) {
  bool prime = true;
  if (n<=1) { prime = false; }
  long lim = sqrt(n)+1;
  for (long ii = 2; ii < lim; ii++){
    if (n%ii==0) { prime = false; }
  }
  return prime;
}

// Given an array with six numbers that hold the differences of a hexagon's number
// with the numbers of its neighbors, how many of those are prime?
long countPrimes(long* current){
  long count = 0;
  for (long ii = 0; ii < 6; ii++){
    if (isPrime(current[ii])) { count++; }
  }
  return count;
}

// The differences for a hexagon of each letter can be calculated by looking at a hexagon
// of similar type, i.e. similar letter, in the previous ring.
// Ultimately only letters A and M matter.
void addNextLevelLetter (long* current, long hex) {
  char lett = letter(hex);
  switch(lett){
    case 'A':
      current[0]+=6;current[1]+=6;current[2]+=0;current[3]+=6;current[4]+=6;current[5]+=12;
      break;
    case 'B':
      current[0]+=6;current[1]+=6;current[2]+=0;current[3]+=6;current[4]+=6;current[5]+=0;
      break;
    case 'C':
      current[0]+=6;current[1]+=6;current[2]+=6;current[3]+=0;current[4]+=6;current[5]+=0;
      break;
    case 'D':
      current[0]+=0;current[1]+=6;current[2]+=6;current[3]+=0;current[4]+=6;current[5]+=6;
      break;
    case 'E':
      current[0]+=0;current[1]+=6;current[2]+=6;current[3]+=6;current[4]+=0;current[5]+=6;
      break;
    case 'F':
      current[0]+=6;current[1]+=0;current[2]+=6;current[3]+=6;current[4]+=0;current[5]+=6;
      break;
    case 'G':
      current[0]+=6;current[1]+=0;current[2]+=6;current[3]+=6;current[4]+=6;current[5]+=0;
      break;
    case 'H':
      current[0]+=6;current[1]+=6;current[2]+=0;current[3]+=6;current[4]+=6;current[5]+=0;
      break;
    case 'I':
      current[0]+=0;current[1]+=6;current[2]+=0;current[3]+=6;current[4]+=6;current[5]+=6;
      break;
    case 'J':
      current[0]+=0;current[1]+=6;current[2]+=6;current[3]+=0;current[4]+=6;current[5]+=6;
      break;
    case 'K':
      current[0]+=6;current[1]+=0;current[2]+=6;current[3]+=0;current[4]+=6;current[5]+=6;
      break;
    case 'L':
      current[0]+=6;current[1]+=0;current[2]+=6;current[3]+=6;current[4]+=0;current[5]+=6;
      break;
    case 'M':
      current[0]+=6;current[1]+=6;current[2]+=12;current[3]+=6;current[4]+=0;current[5]+=6;
      break;
    default:
      int junk = 3;
  }   
  

}

int main()
{
  long current[6] = { 0, 0, 0, 0, 0, 0};                // initialize the six differences for current hexagon
  long lastbyletter[13][6];                             // table to hold diffs for 13 letters A-M of last ring
  long currbyletter[13][6];                             // table to hold diffs for 13 letters A-M of curr ring
  long countthrees = 0;                                 // keeps track of how many hexagons with 3 primes 
  long ringnum = -1;                                    // initialization of var to keep track of current ring
  for (long ii = 1; ii <= 37 ; ii++) {                  // process first 37 hexagons (rings 0-2) to establish pattern
    startertable(current,ii);
    if ( countPrimes(current) == 3) { countthrees++; }
    if ( ring(ii) > ringnum ) { ringnum = ring(ii); std::cout << " new ring " << ringnum << "\n"; }
    else { std::cout << "\n";}
    for (int jj = 0; jj < 6; jj++) {
      lastbyletter[int(letter(ii))-65][jj]=current[jj];
      currbyletter[int(letter(ii))-65][jj]=current[jj];
    }
  }


  long long  ii = 38;                                   // counter for current hexagon
  long increment = 24;                                  // how many hexagons in current ring
  while ( countthrees < 2000) {                         // problem asks for 2000th 3-prime hexagon
    
    bool newring = false;                               // only need to check two hex per ring, A and M
    if ( ring(ii) > ringnum ) {
      newring = true;
      ringnum = ring(ii);
      for ( int aa = 0; aa < 13; aa++) {
        for ( int bb = 0; bb < 6; bb++) {
          lastbyletter[aa][bb]=currbyletter[aa][bb];    // if new ring, update tables with last and curr diffs
        }
      }
    }
    for (int jj = 0; jj < 6; jj++) {
      current[jj]=lastbyletter[int(letter(ii))-65][jj]; // find diffs for this hex by looking at A hex last ring
    }
    addNextLevelLetter(current,ii);
    for (int jj = 0; jj < 6; jj++) {
      currbyletter[int(letter(ii))-65][jj]=current[jj]; // keep track of current diffs to use in next ring level
    }
    if ( countPrimes(current) == 3) { countthrees++; }  // noted if have 3 primes
    //print hexagons with 3 primes if want to keep track as it works
    if ( countPrimes(current) == 3 ) {
      std::cout << ii << " " << " primes " << countPrimes(current) << " countthrees " << countthrees ;
      if ( newring ) { std::cout << " new ring " << ringnum << "\n"; }
      else { std::cout << "\n";}
    }




    ii += increment-1;                                  // jump all the way to last hex in this ring, M
    newring = false;                                    // logic the same as above; this is not a new ring though
    if ( ring(ii) > ringnum ) {
      newring = true;
      ringnum = ring(ii);
      for ( int aa = 0; aa < 13; aa++) {
        for ( int bb = 0; bb < 6; bb++) {
          lastbyletter[aa][bb]=currbyletter[aa][bb];
        }
      }
    }
    for (int jj = 0; jj < 6; jj++) {
      current[jj]=lastbyletter[int(letter(ii))-65][jj];
    }
    addNextLevelLetter(current,ii);
    for (int jj = 0; jj < 6; jj++) {
      currbyletter[int(letter(ii))-65][jj]=current[jj];
    }
    if ( countPrimes(current) == 3) { countthrees++; }
    //print hexagons with 3 primes if want to keep track as it works
    if ( countPrimes(current) == 3 ) {
      std::cout << ii << " " << " primes " << countPrimes(current) << " countthrees " << countthrees ;
      if ( newring ) { std::cout << " new ring " << ringnum << "\n"; }
      else { std::cout << "\n";}
    }

    ii+=1;                                              // next hex is first in the next ring
    increment += 6;                                     // next ring has 6 more hexagons than this one
  }

}

