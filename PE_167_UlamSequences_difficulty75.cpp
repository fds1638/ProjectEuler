// Done July 14 2020
// Solve Project Euler number 167, Ulam sequences.
// https://projecteuler.net/problem=167
// Difficulty 75%.
// I am the 1507th person to solve it since 2007.
// Find 10^11th Ulam sequence number for several values of n, and find the sum of those.
// Ulam sequnce starts with two numbers, then includes numbers which are sum of previous
// numbers in exactly one way.
// Solution relies on two insights. First, for the problem all Ulam sequences have only
// two even numbers. Second, the pattern of gaps between Ulam numbers repeats.

#include <iostream>
#include <array>
#include <math.h>
#include <algorithm>
#include <unordered_map>
#include <iostream>
using namespace std;

std::unordered_map<long, long> themap;  // map of numbers which are (not) Ulam numbers

int main()
{
  int lo = 2;                     // problem states one of numbers is 2
  long long totalsum = 0;         // keeps track of total sum problem asks for

  for (int n = 2; n <= 10; n++ ) {  // problem specifies 2<=n<=10

    int hi = 2*n+1;               // the other number starting the sequence
 
    int sml = lo;                 // recognize that all numbers in Ulam sequence are odd, except 2 and ...
    int lrg = lo + 2*hi;          // ... lo + 2*hi
    long count = 2;               // keeps track of number of Ulam sequence numbers for this value of n; count two even numbers above

    int needstreak = lrg/2;       // Each Ulam sequence odd numbers starts with a streak of numbers in the sequence.
                                  // Calc how many are in that sequence because will look for that sequence to repeat again.
    themap[hi]=1;                 // themap will keep track of which numbers are in sequence and which not.
    count++;                      // Now count=3, the number 2, the other even number lrg, and the second starting number 2*n+1.

    // Fill out the rest of the streak of odd numbers in the Ulam sequence.
    // No need to put even numbers in themap, since we counted them already.
    for (long ii = 1; ii < lrg/2; ii++) {
      themap[hi+2*ii]=1;
      count++; 
    }  

    // This keeps finding new numbers in Ulam sequence by checking wether a previous odd number differs by 
    // either 2 or by lrg, but not by both. Puts either 1 or a 0 in themap. Since know each odd number in 
    // Ulam sequence differs from another in the sequence by at most lrg, can erase unneeded values from themap.
    // Also this loop looks for the streak to reappear, so we know when the pattern in Ulam sequences reappears 
    // for this value of n.
    int jj = hi + lrg;
    int streak = 0;
    while ( streak < needstreak ) {
      if ( ( themap[jj-sml]==1 && themap[jj-lrg]==0 ) || ( themap[jj-sml]==0 && themap[jj-lrg]==1 ) )  {
        themap[jj]=1;
        count++;
        streak++;
      } else {
        themap[jj] = 0;
        streak = 0;
      } 
      themap.erase(jj-lrg);
      jj += 2;
    }

    // Now that we have found where the streak reoccurs, we know the periodicity.
    // We know that for each n want 10^11th Ulam sequence number, so using periodicity
    // find how many periods that is and jump to the highest full period below 10^11 numbers.
    // I could have done this with fewer variables.
    long patnumend = jj-2;
    long pattnumbeg = patnumend-lrg+2;
    long patcntbeg = count-needstreak+1;
    long nums_increment = pattnumbeg - hi;
    long count_increment = patcntbeg - 3;
    long countneeded = 100000000000;
    long numjumps = (countneeded-3)/count_increment;

    // These are the numbers from where to start the Ulam sequence counting one-by-one again. 
    long newstartnum = hi+numjumps*nums_increment; 
    long newcountnum = 3+numjumps*count_increment; 
    // This tells me how many Ulam numbers I need to get to 10^11.
    long numwanted;

    // Reset a streak in themap to start counting Ulam numbers one-by-one.
    // If the 10^11th number is in this streak, add it to the totalsum.
    if ( countneeded - newcountnum < needstreak ) {
      numwanted = (countneeded-newcountnum)*2+newstartnum;
      std::cout << "countneeded " << countneeded << " numwanted " << numwanted << "\n";
      totalsum += numwanted;

    } else {  // the 10^11th number is not in the streak, so count one-by-one until it is found. This is exactly like the code above.                  
    
      count = newcountnum;
      themap[newstartnum]=1;
      for (long ii = 1; ii < lrg/2; ii++) {
        themap[newstartnum+2*ii]=1;
        count++; 
      }

      long jjj = newstartnum + lrg;
      while ( count < countneeded ) {
        if ( ( themap[jjj-sml]==1 && themap[jjj-lrg]==0 ) || ( themap[jjj-sml]==0 && themap[jjj-lrg]==1 ) )  {
          themap[jjj]=1;
          count++;
        } else {
          themap[jjj] = 0;
        } 
        themap.erase(jjj-lrg);
        jjj += 2;
      } // end while

      std::cout << "count " << count << " last " << jjj-2 << "\n";
      totalsum += jjj-2;

    } // end else  

    std::cout << "totalsum " << totalsum << "\n";
    std::cout << "\n";

  }  
  return 0;
}

