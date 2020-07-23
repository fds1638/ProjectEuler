// Done July 23 2020
// Solve Project Euler problem 198, Ambiguous Numbers
// https://projecteuler.net/problem=198
// Difficulty 80%, am the 998th to solve it (problem posted 2008).
// Ambiguous numbers are defined as numbers whose best rational approximation
// is by two rational numbers. Thus we are looking for fractions equidistant
// on the number line from other fractions, with a limit of size of denominator.
// Note: zero is one of the fractions to be equidistant from.

// Note: this is a lot slower than the other solutions posted on the Project Euler
// website. But then I didn't know the number theory they used, so I'll give myself
// credit for having solved it without some of the theoretical tools they used.

#include <iostream>
#include <array>
#include <math.h>
#include <algorithm>
#include <unordered_map>
#include <iostream>
using namespace std;

// Ambiguous numbers are formed when allowing a larger denominator, here b,
// makes a fraction equidistant to a fraction with a smaller denominator, here a.
// For fractions like this to work, a and b must be mutually prime.
// For no other fraction to be closer, the two fractions with denominators a and b
// must differ by one in the numerator when put over a common denominator.
// If a and b mutually prime, finds numerators so that that difference is 1.
// If a and b not mutually prime, returns zeros.
pair<long,long> diffbyone(long a, long b) {
  // assume a < b, though not necessary
  long m = 1;
  while ( (m*b)%a!=1 && (m*b)%a!=a-1 && (m*b)%a!=0 ) { 
    m++; 
  }
  long n=-1;
  if ( (m*b)%a==1 ) { n = (m*b-1)/a;}
  else if ( (m*b)%a==a-1 ) { n = (m*b+1)/a; }
  else { m=0; n=0; }
  return make_pair(n,m);
}


int main()
{
long count=0;                                   // keep count of ambiguous numbers found
for (long a=2; a<=25000000; a++ ) {             // problem says denom less than 10^8, which limits a
for (long b=a+1; b<=50000000/a+2; b++) {        // given a, b limited by common denominator being less than 10^8

  pair<long,long> numerators = diffbyone(a,b);        // find the numerators so that the two fractions differ by 1 
  long p = numerators.second;
  long q = numerators.first;
  if ( p!=0 && q!=0 ) {
    double af=a;
    double bf=b;
    double pf=p;
    double qf=q;
    if ( (pf/af+qf/bf)/2.0<=1.0/100.0 && b*a<=100000000/2) {      // check if ambiguous number is smaller than 1/100 and has 
                                                                  // denominator less than 10^8 
      count++;
    }
  }
}
}

count += 50000000-50;                    // account for fractions that are between smallest current denominator and zero
std::cout << "count " << count << endl;
return 0;
}

