// Done July 8 2020
// Solves Project Euler problem 157
// https://projecteuler.net/problem=157
// Difficulty 65%

// Consider the equation 1/a + 1/b = p/(10^n)
// where a, b, p, and n are integers.
// How many solutions exist for 1<=n<=9

  
#include <iostream>
#include <array>
#include <math.h>
using namespace std;


// The key is to not make the search space too big.
// For a given n, we consider all possibilities of a, which goes from 1 to 2*(10^n).
// Then given a, p can't lead to a fractions more than 2 * (1/a)
// and p can't lead to a fraction less than 1 * (1/a).
// Then we find b's such that a, p, and b are integers.
// Note that once a is greater than 1*(10^n), there is only one possibility for p.
// That makes searching a lot quicker than it could be.
int main()
{
  long count = 0;
  for (long n = 1; n <= 9; n++) {
    long n10 = pow(10,n);
    for (long a = 1; a <= (2*n10); a++) {
      for (long p = (2*n10)/a; p > n10/a; p--){
        //std::cout << "a " << a << " p " << p  << " ratio " << (10*a)/(p*a-10) << "\n";
        if ( p*a-n10!=0 && (n10*a)%(p*a-n10) == 0 ) {
          long b = (n10*a)/(p*a-n10);
          std::cout << "n " << n << " a " << a << " b " << b << " p " << p  << "\n";
          count++;


        }
      }
    }
  }

  std::cout << "\n";
  std::cout << "count " << count << "\n";

}

