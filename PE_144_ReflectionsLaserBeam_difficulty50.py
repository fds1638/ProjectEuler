# Done on July 3 2020
# This solve Project Euler problem 144, Investigating multiple reflections of a laser beam.
# Difficulty 50%.
# https://projecteuler.net/problem=144
# A laser beam shines into a small hole in an ellipse at the very "top."
# The task is to find how many times is reflects within the ellipse before it
# escapes through the same small hole.
# Basically, geometry and reflecting points and vectors, then finding the
# intersection of the new line with the ellipse.
# Repeat until y of the new intersection point with the ellipse is too high,
# i.e. the laser has gone out the hole at the top.

import numpy as np
import csv
from numpy import genfromtxt

# problem gives this starting point for the laser,
# just outside the hole
x1 = 1407.0/197965.0
y1 = 1979648.0/197965.0
m = -197.0/14.0
b = y1 - m * x1
out = False
ii = 0 # count reflections

while not out:
    ii += 1
    # I know the equation of line and ellipse
    # and I know one of the intersections from previous iteration.
    # Thus can use factoring formula to find the other intersection.
    newx = (b*b-100.0)/( x1 * (4.0+m*m))
    newy = m * newx + b

    # Check if the new intersection is in the hole.
    if newy > 9.99997999998: 
        out = True

    # Calculate the reflection.
    # First, pretend there was no ellipse there, so the laser
    # goes through an equal distance outside the ellipse.
    x_thru = (newx - x1) + newx
    y_thru = (newy - y1) + newy

    # The problem gives use the formula for the slope of the tangent at a point.
    # Find the slope of the normal (perpendicular) to the ellipse at that point.
    m_tang = -4.0*newx/newy
    m_perp = -1.0/m_tang

    # Take the projected point through, put a line through it perpendicular to the tangent,.
    # Calculate intersection point with tangent line.
    x_int = (m_tang*newx-newy-m_perp*x_thru+y_thru)/(m_tang-m_perp)
    y_int = m_perp*x_int-m_perp*x_thru+y_thru

    # Reflect thru point over tangent line to find a point in the new
    # reflected line of the laser.
    x_refl = 2*x_int-x_thru
    y_refl = 2*y_int-y_thru

    # Calculate the new slope and update variables.
    m = (y_refl-newy)/(x_refl-newx)
    x1 = newx
    y1 = newy
    b = y1 - m * x1

print("num reflections", ii-1) #the last reflection didn't really happen

