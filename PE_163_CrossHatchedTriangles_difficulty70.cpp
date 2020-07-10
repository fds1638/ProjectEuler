// Done July 10 2020
// Solves Project Euler problem 163, Cross Hatched Triangles.
// https://projecteuler.net/problem=163
// Difficulty 70% (solved by only 1623, including me).
// Problem asks to count number of triangles (including triangles within triangles)
// in a picture with about 320 lines in it.

// My solution was to take three non-parallel lines at a time and find their
// three intersections. If all three intersection points are within the bounds
// of the graph, then the triangle was counted as valid.

#include <iostream>
#include <array>
#include <math.h>
#include <algorithm>
#include <unordered_map>
#include <iostream>
using namespace std;

// The lines one of six slopes when put on a Cartesian grid.
// The angles these lines formed with the positive x-axis are, in order
// 0, 90, 60, 120, 30, 150.
// 1 x=b
// 2 y=b
// 3 y=sqrt(3)*x+b
// 4 y=-sqrt(3)*x+b
// 5 y=1/sqrt(3)*x+b
// 6 y=-1/sqrt(3)*x+b

// If I know the slopes of the two lines and the y-intercepts (determined by type and b-value),
// I can calculate the x-coordinate of the intersection point.
float x_intersection(int type1, int type2, float b1, float b2) {
  float x;
  if ( type1 == 1  && type2 == 2 ) { x = b1; }
  else if ( type1 == 1  && type2 == 3 ) { x = b1; }
  else if ( type1 == 1  && type2 == 4 ) { x = b1; }
  else if ( type1 == 1  && type2 == 5 ) { x = b1; }
  else if ( type1 == 1  && type2 == 6 ) { x = b1; }
  else if ( type1 == 2  && type2 == 3 ) { x = (b1-b2)/sqrt(3.0); }
  else if ( type1 == 2  && type2 == 4 ) { x = (b2-b1)/sqrt(3.0); }
  else if ( type1 == 2  && type2 == 5 ) { x = (b1-b2)*sqrt(3.0); }
  else if ( type1 == 2  && type2 == 6 ) { x = (b2-b1)*sqrt(3.0); }
  else if ( type1 == 3  && type2 == 4 ) { x = (b2-b1)/(2.0*sqrt(3.0)); }
  else if ( type1 == 3  && type2 == 5 ) { x = (b2-b1)/2.0*sqrt(3.0); }
  else if ( type1 == 3  && type2 == 6 ) { x = (b2-b1)/4.0*sqrt(3.0); }
  else if ( type1 == 4  && type2 == 5 ) { x = (b1-b2)/4.0*sqrt(3.0); }
  else if ( type1 == 4  && type2 == 6 ) { x = (b1-b2)/2.0*sqrt(3.0); }
  else if ( type1 == 5  && type2 == 6 ) { x = (b2-b1)/2.0*sqrt(3.0); }
  return x;
}

// If I know the slopes of the two lines and the y-intercepts (determined by type and b-value),
// I can calculate the y-coordinate of the intersection point.
float y_intersection(int type1, int type2, float b1, float b2) {
  float y;
  if ( type1 == 1  && type2 == 2 ) { y = b2; }
  else if ( type1 == 1  && type2 == 3 ) { y = sqrt(3.0)*b1+b2; }
  else if ( type1 == 1  && type2 == 4 ) { y = -sqrt(3.0)*b1+b2; }
  else if ( type1 == 1  && type2 == 5 ) { y = b1/sqrt(3.0)+b2; }
  else if ( type1 == 1  && type2 == 6 ) { y = -b1/sqrt(3.0)+b2; }
  else if ( type1 == 2  && type2 == 3 ) { y = b1; }
  else if ( type1 == 2  && type2 == 4 ) { y = b1; }
  else if ( type1 == 2  && type2 == 5 ) { y = b1; }
  else if ( type1 == 2  && type2 == 6 ) { y = b1; }
  else if ( type1 == 3  && type2 == 4 ) { y = b1/2.0+b2/2.0; }
  else if ( type1 == 3  && type2 == 5 ) { y = 1.5*b2-0.5*b1; }
  else if ( type1 == 3  && type2 == 6 ) { y = 0.75*b2+0.25*b1; }
  else if ( type1 == 4  && type2 == 5 ) { y = 0.75*b2+0.25*b1; }
  else if ( type1 == 4  && type2 == 6 ) { y = -0.5*b1+1.5*b2; }
  else if ( type1 == 5  && type2 == 6 ) { y = 0.5*b1+0.5*b2; }
  return y;
}

// For each type (i.e. slope) of line, I give the lower bound of the
// range of the y-intercepts to use.
// For type 1, i.e. vertical line, it is x-intercepts.
float loBound(int type) {
  float lo;
  if ( type == 1 ) { lo = 0.5; }
  else if ( type == 2 ) { lo = 0.0; }
  else if ( type == 3 ) { lo = -35.0*sqrt(3.0); }
  else if ( type == 4 ) { lo = sqrt(3.0); }
  else if ( type == 5 ) { lo = -35.0/sqrt(3.0); }
  else if ( type == 6 ) { lo = 1.0/sqrt(3.0); }
  return lo;
}

// For each type (i.e. slope) of line, I give the upper bound of the
// range of the y-intercepts to use.
// For type 1, i.e. vertical line, it is x-intercepts.
float hiBound(int type) {
  float hi;
  if ( type == 1 ) { hi = 35.5+0.1; }
  else if ( type == 2 ) { hi = 35.0*sqrt(3.0)/2.0+0.1; }
  else if ( type == 3 ) { hi = 0.0+0.1; }
  else if ( type == 4 ) { hi = 36.0*sqrt(3.0)+0.1; }
  else if ( type == 5 ) { hi = 35.0/sqrt(3.0)+0.1; }
  else if ( type == 6 ) { hi = 71.0/sqrt(3.0)+0.1; }
  return hi;
}

// For each type of line, i.e. slope, give the step size.
float step(int type) {
  float step;
  if ( type == 1 ) { step = 0.5; }
  else if ( type == 2 ) { step = sqrt(3.0)/2.0; }
  else if ( type == 3 ) { step = sqrt(3.0); }
  else if ( type == 4 ) { step = sqrt(3.0); }
  else if ( type == 5 ) { step = 1.0/sqrt(3.0); }
  else if ( type == 6 ) { step = 1.0/sqrt(3.0); }
  return step;
}




int main()
{
  int count = 0;       // count valid triangles
  int checked = 0;     // count of intersections checked, used for debugging

  // For six slopes of lines, choose three at a time to check whether they intersect
  // in a valid triangle. 6C3 = 20 different combinations.
  for (int ii = 1; ii <=4 ; ii++) {
    float step1 = step(ii);
    float hi1 = hiBound(ii);
    for (int jj=ii+1; jj <= 5; jj++ ) {
      float step2 = step(jj);
      float hi2 = hiBound(jj);
      for (int kk=jj+1; kk<=6; kk++ ) {
        float step3 = step(kk);
        float hi3 = hiBound(kk);
        
        // Once three types of lines chosen, loop through x- and y-intercepts, as appropriate.
        float b1 = loBound(ii);
        while ( b1 < hi1 ) {
          float b2 = loBound(jj);
          while ( b2 < hi2 ) {
            float b3 = loBound(kk);
            while ( b3 < hi3 ) {
              float x1 = x_intersection(ii,jj,b1,b2);  // calculate three intersection points
              float y1 = y_intersection(ii,jj,b1,b2);
              float x2 = x_intersection(ii,kk,b1,b3);
              float y2 = y_intersection(ii,kk,b1,b3);
              float x3 = x_intersection(jj,kk,b2,b3);
              float y3 = y_intersection(jj,kk,b2,b3);

              int inside = 1;  // assume triangle valid unless one point found outside big triangle

              // On the Cartesian plane, want all triangles within big triangle of (0,0), (36,0), (18,18sqrt(3)).
              // Check to make sure all three points of intersection within that big triangle.
              // Give a tolerance epsilon just so floating point rounding doesn't cause a problem.
              // At the end, make sure have three distinct points rather than three concurrent lines.
              float epsilon = 0.05;
              if ( y1 < 0.0-epsilon ) { inside = 0; }
              else if ( y1 > sqrt(3.0)*x1+epsilon ) { inside = 0; }
              else if ( y1 > -sqrt(3.0)*(x1-36.0)+epsilon ) { inside = 0; }            
              else if ( y2 < 0.0-epsilon ) { inside = 0; }
              else if ( y2 > sqrt(3.0)*x2+epsilon ) { inside = 0; }
              else if ( y2 > -sqrt(3.0)*(x2-36.0)+epsilon ) { inside = 0; }            
              else if ( y3 < 0.0-epsilon ) { inside = 0; }
              else if ( y3 > sqrt(3.0)*x3+epsilon ) { inside = 0; }
              else if ( y3 > -sqrt(3.0)*(x3-36.0)+epsilon ) { inside = 0; }            
              else if ( abs(x1-x2)<0.01 && abs(x1-x3)<0.01 && abs(x2-x3) < 0.01 && abs(y1-y2)<0.01 && abs(y1-y3)<0.01 && abs(y2-y3) < 0.01 ) { inside = 0; }

              checked++;
              if ( inside == 1 ) { count++; }     // add to count

              b3 += step3;
            }
            b2 += step2;
          }
          b1 += step1;
        }                

        // If want to keep track of how progress is going. But really it's too fast to matter.
        // std::cout << "checked " << ii << " " << jj << " " << kk << "\n";

      }
    }
  }  

  // print out results
  std::cout << "checked " << checked << " triangles, found " << count << " triangles." << "\n";

}

