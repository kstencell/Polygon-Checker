//
// Group Assignment
// CSCN71020 - F20
// Karl Stencell, Thomas Horvath, Gautam Singh - Dec 2020
//
// REVISION HISTORY
// 1.0		2020-Nov-26		initial
//
// VERSION 1.0 NOTES
// This file contains all the functionality needed to analyze a triangle and calculate the inner angle of a triangle.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "triangleSolver.h"

char* analyzeTriangle(int side1, int side2, int side3)  // Determines the type of triangle given its side lengths
{
	char* result = "";
	if (!checkValidDimensions(side1, side2, side3)) // The side lengths dont make sense.
	{
		result = "Not a triangle";
	}
	else if (side1 == side2 && side1 == side3) // Below are the conditions for triangle types dependent on their side lengths.
	{
		result = "Equilateral triangle";
	}
	else if ((side1 == side2 && side1 != side3) || 
			 (side1 == side3 && side1 != side2)
		   ||(side2 == side3 && side2 != side1))
	{
		result = "Isosceles triangle";
	}
	else {
		result = "Scalene triangle";
	}

	return result;
}

double* calculateAngles(double side1, double side2, double side3) // Given 3 side lengths this will calculate the inner 3 angles of the triangle using the cosine law.
{
	double* angles = malloc(3 * sizeof(double));

	angles[0] = (180 / PI) * acos((pow(side2, 2) + pow(side3, 2) - pow(side1, 2)) / (2 * (double)side2 * (double)side3));
	angles[1] = (180 / PI) * acos((pow(side3, 2) + pow(side1, 2) - pow(side2, 2)) / (2 * (double)side3 * (double)side1));
	angles[2] = 180 - angles[0] - angles[1];

	return angles;
}

bool checkValidDimensions(int side1, int side2, int side3) // Check if the sides form a triangle
{
	if (side1 + side2 <= side3 || side1 + side3 <= side2 || side2 + side3 <= side1) // The only conditions that constitute triangle legitimacy
		return false;
	else if (side1 <= 0 || side2 <= 0 || side3 <= 0) // negative side lengths also dont make sense.
		return false;
	else
		return true;
}