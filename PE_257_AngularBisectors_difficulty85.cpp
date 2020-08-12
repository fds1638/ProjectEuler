// Done August 12, 2020
// Solves Project Euler problem 257, Angular Bisectors
// https://projecteuler.net/problem=257
// Difficulty: 85%. I am 611th person to solve this since 2009.

// Given a triangle, find integer combinations of the sides a, b, c such that
// when draw angular bisectors to define four smaller triangles, one of those
// smaller triangles has an integer ratio.

// Because of how the problem defines a, b, and c and the particular sub-triangle
// whose area we are looking for, we know that the integer ratios can be either
// 1/2, 1/3, or 1/4 (or, if you prefer, 2, 3, or 4). This is because a<=b<=c so
// the ratios of the sides of the particular subtriangle are not less than half
// the corresponding sides of original triangle (angle bisector theorem).

// Thus we know we have 33,333,333 ways to get a ratio of 4, since we need equilateral
// triangles to get each side of sub-triangle to be 1/2 of original side. The code below
// doesn't compute that, I just added that onto the number the code below gave me.

// The code below finds the number of triangles which have ratios of two or three. First,
// if a is smallest side, set a=1, and figure out the values b can have if there is going
// to be an area ratio of 1:2 for the triangles, keeping in mind a<=b<=c and a+b>c. This 
// yields 2 < b < 1+sqrt(2). Then can loop through and find integer combinations of a, b, and c
// which meet these ratios. To avoid double-counting, always reduce a, b, and c to be mutually
// prime and put that in the map, then scale up as many times as you can using the multiplier
// while keeping a+b+c<=limit (the problem sets the limit at 100,000,000).

// Do the same thing for area ratios of 1:3. Here 1 < b < (1+sqrt(3))/2.

// Then increase the bdenom (base denominator) starting at 1 to find appropriate integer values
// of a, b, and c. At around 13000 I get a steady state of the count as xxxxxxxxx (not putting
// the answer here). Add that to the 33,333,333 noted above for the final answer.

#include <iostream>
#include <array>
#include <math.h>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <iostream>
#include <vector>

using namespace std;

//std::map<vector<int>, int> themap;  // map of numbers which are (not) Ulam numbers
//map<vector<int>, int> vis; 
//std::unordered_map<int[3], int> themap;
//std::unordered_map<pair<int,int>, int> themap;

typedef std::array<int, 3> abcarray;
std::map<abcarray, int> trianglemap;

int gcd(int a, int b) {
  if ( a<b ) {
    if ( a ==0 ) { return b; }
    return gcd( b%a, a );
  } else {
    if (b==0) { return a; }
    return gcd ( a%b, b);
  } 

}


int main()
{
long limit = 100000000;
long long count=0;
long maxprod = INT_MIN;
//long bdenom = 1;
for (int bdenom=1; bdenom<=limit/5; bdenom++) {
  int count2 = 0;
  int count3 = 0;
  int count4 = 0;

  for (int n = 2*bdenom+1; n<=floor( bdenom*(1+pow(2,0.5)) ); n++) {
    int a = bdenom*(n-bdenom);
    int b = n*(n-bdenom);
    int c = bdenom*(n+bdenom);
    int rf = gcd(gcd(a,b),c);
    a = a/rf;
    b = b/rf;
    c = c/rf;
    abcarray curarray = {a, b, c};
    if ( trianglemap.find(curarray)==trianglemap.end() ) {
      trianglemap[curarray]=1;
      int multiplier = 1;
      while ( multiplier*(a+b+c)<=limit && a+b>c && c>=b ) {
      //if ( a+b+c<=limit && a+b>c && c>=b ) {
        count2++;
        //std::cout<<"aa "<<a<<" b "<<b<<" c "<<c<<" sum "<<a+b+c<<" ratio "<< (a+b) * (a+c)/b/c <<endl;
        multiplier++;
      }
    } 
  }

  for (int n = bdenom+1; n<=floor( bdenom*(1+pow(3,0.5))/2.0 ); n++) {
    int a = bdenom*(2*n-bdenom);
    int b = n*(2*n-bdenom);
    int c = bdenom*(n+bdenom);
    int rf = gcd(gcd(a,b),c);
    a = a/rf;
    b = b/rf;
    c = c/rf;
    abcarray curarray = {a, b, c};
    if ( trianglemap.find(curarray)==trianglemap.end() ) {
      trianglemap[curarray]=1;
      int multiplier = 1;
      while ( multiplier*(a+b+c)<=limit && a+b>c && c>=b ) {
      //if ( a+b+c<=limit && a+b>c && c>=b ) {
        count3++;
        //std::cout<<"aa "<<a<<" b "<<b<<" c "<<c<<" sum "<<a+b+c<<" ratio "<< (a+b) * (a+c)/b/c <<endl;
        multiplier++;
      }
    } 
  }



/*
  for (int m=ceil( (1+pow(3,0.5))/2*a ); m<=2*a; m++) {
  //for (int m=a; m<=2*a; m++) {
    if ( (a*a+m*a)%(2*m-a)==0 ) {
      int b = (a*a+m*a)/(2*m-a);
      int c = (a*a+a*b)/(2*b-a);
      if ( a+b+c<=limit && a+b>c ) {
      //if ( a+b+c<=limit && a+b>c && c>=b ) {
        count3++;
        std::cout<<"a "<<a<<" b "<<b<<" c "<<c<<" m "<<m<<" ratio "<<((a+b)*(a+c))/(b*c)<<endl;

      }
    }
  }

  
  for (int k=ceil( a*pow(2,0.5)  ); k<=2*a; k++) {
    if ( (2*a*a)%k==0 ) {
      int b = 2*a*a/k+a;
      int c = a+k;
      if ( a+b+c<=limit && a+b>c && c>=b ) {
        count2++;
        //std::cout<<"aa "<<a<<" b "<<b<<" c "<<c<<" sum "<<a+b+c<<" ratio "<< (a+b) * (a+c)/b/c <<endl;

      }
      

    }
    //if ( (a*a+n*a)%(n-a)==0 ) {
    //  int b = (a*a+n*a)/(n-a);
    //  int c = (a*a+a*b)/(b-a);

    //}
  }
*/

  count += count2 + count3 + count4;

  if (bdenom%1000==0) {
    std::cout<<"done "<<bdenom<<" count "<<count<<endl;
  }
}

std::cout<<"final count "<<count<<endl;



return 0;
}

