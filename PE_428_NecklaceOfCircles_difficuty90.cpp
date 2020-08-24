// Done 24 August 2020
// Solves Project Euler problem 428, A Necklace Of Circles
// https://projecteuler.net/problem=428
// Difficulty: 0.90 ( on a scale of 0 to 1 ).
// I am the 213th person to solve this since the problem was posted in 2013.

// This was the hardest Project Euler problem that I have done, and I am
// very proud of having finished it. This code is really slow because I
// ended up factoring all the numbers up to 1 billion. I tried to figure out
// a sieve to use, but had trouble doing so, and at some point I realized
// I wouldn't figure it out before this slow code was finished. However,
// when I looked at the solutions discussion thread on the Project Euler
// website, I saw that a number of people had inefficient code and a lot
// of other people looked up formulas which they used.

// This problem is based on sets of tangent circles called Steiner circles. 
// The one big hint from the wikipedia page for Steiner circles that I got
// was to consider an inversion, i.e. a mapping which transforms the inner
// and outer boundary circles into concentric circles. Other than that, it 
// was a lot of slow and painstaking work for me to have a series of 
// small epiphanies which led to the solution. An outline:

// I realized that only three sets of concentric Steiner circles could
// possibly be mapped by inversion to circles with integers for a, b, and
// c as specified in the problem.

// By taking b as given, and finding a relationship between a and c, I found
// that the integers I was looking for like on three hyperbolas for each given
// value of b.

// Then it was a matter of finding where those hyperbolas intersected lattice
// points, which involved prime factors of 2b^2, 4b^2, and 12b^2, with the 4b^2
// factor further needing to be broken down into prime factors which were
// equal to 1 modulo 3 and prime factors equal to 2 modulo 3.

// At this point I ended up just factorizing all the possible values of b.

// Last note: working my way through this problem involved a lot of dead ends,
// but some of those led to interesting facts, such as figuring out that the
// centers of the necklace circles lie on an ellipse (a fact which I later saw
// on wikipedia).


 
#include <iostream>
#include <array>
#include <math.h>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <iostream>
#include <vector>

using namespace std;


int main()
{

long long a, b, c;

long limit = 1000000000;
//long limit = 3000;
// usually start with count=0 and b=1, but was restarting
// from these values because of an unscheduled interruption.
long long count=260431007172;

for ( b=380000001; b<=limit ; b++ ) {

  // some duplication of variables here because I was
  // copying over from other attempts
  long n = b;
  long norig=n;
  // prod1 and prod2 deal with the 1 mod 3 and 2 mod 3 factors
  long prod1=1, prod2=1;
  // the count variables each store the number of points on
  // one of the three hyperbolas for this value of b
  long count2=1, count12=1, count4=1;
  // deal with factors of TWO
  // essentially factorize b, use it to quickly figure out
  // the count variables for 2b^2, 4b^2, and 12b^2
  // and add them up. then go to next b.
  long factorcount = 0;
  while ( n%2==0 ) {
    factorcount++;
    n=n/2;
  }
  if ( factorcount==0 ) { 
    prod2*=3;
    count2*=2;
    count4*=3; 
    count12*=3; 
  }
  else { 
    prod2*=2*factorcount+2+1;
    count2*=2*factorcount+1+1;
    count4*=2*factorcount+2+1;
    count12*=2*factorcount+2+1;
  }
  // deal with factors of THREE
  factorcount=0;
  while ( n%3==0 ) {
    factorcount++;
    n=n/3;
  }
  if ( factorcount==0 ) { 
    prod1*=1; 
    count2*=1;
    count4*=1;
    count12*=2; 
  }
  else { 
    prod1*=2*factorcount+1; 
    count2*=2*factorcount+1;
    count4*=2*factorcount+1-2;
    count12*=2*factorcount+1+1;
  }
  // deal with factors of FIVE or more
  factorcount=0;
  long ii=5;
  while ( ii<=pow(n,0.5) ) {
    factorcount=0;
    while ( n%ii==0 && n>1 ) {
      factorcount++;
      n=n/ii;
    }
    if ( ii%3==1 ) {
      if ( factorcount==0 ) { 
        prod1*=1; 
        count2*=1; 
        count4*=1; 
        count12*=1; 
      }
      else { 
        prod1*=2*factorcount+1;
        count2*=2*factorcount+1;
        count4*=2*factorcount+1;
        count12*=2*factorcount+1;
      }
    } else {
      if ( factorcount==0 ) { 
        prod2*=1; 
        count2*=1; 
        count4*=1; 
        count12*=1; 
      }
      else { 
        prod2*=2*factorcount+1; 
        count2*=2*factorcount+1; 
        count4*=2*factorcount+1; 
        count12*=2*factorcount+1; 
      }
    }
    ii+=2;
  }
  // in case n is prime greater than 2
  if ( n > 2 ) { 
    if ( n%3==1 ) {
      prod1*=2*1+1; 
      count2*=2*1+1; 
      count4*=2*1+1; 
      count12*=2*1+1; 
    } else {
      prod2*=2*1+1; 
      count2*=2*1+1; 
      count4*=2*1+1; 
      count12*=2*1+1; 
    }
  }

  // deal with putting together the info for count4
  // depending on prod1 and prod2
  long retprod;
  if ( norig%3==1 ) {
    retprod=(prod2/2)*prod1;
  } else {
    retprod=(prod2/2+1)*prod1;
  }
  if ( b%3!=0 ) { count4=retprod; }
 
  // add to the count tally before going to next b 
  count += count2 + count4 + count12;

  // keep track of progress, it'll take a while
  if ( b%1000000==0 ) {
    std::cout<<"b "<<b<<" count "<<count<<endl;
  }
}
//give final answer
std::cout<<"b "<<b-1<<" count "<<count<<endl;
return 0;
}
