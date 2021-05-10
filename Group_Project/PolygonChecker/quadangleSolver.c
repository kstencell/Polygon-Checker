//
// Group Assignment
// CSCN71020 - F20
// Karl Stencell, Thomas Horvath, Gautam Singh - Dec 2020
//
// REVISION HISTORY
// 1.0		2020-Dec-14		initial
//
// VERSION 1.0 NOTES
// This file contains all the functionality needed to computer quadrilateral properties given 4 points in coordinate form.
// The coordinates are stored in a 2D array in the form {{x1,y1}, {x2,y2}, {x3,y3}, {x4,y4}}.


#include "quadangleSolver.h"
#include "triangleSolver.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// This function contains my implementation of the Jarvis March technique used to connect points in 2D space in a such a way
// that it creates a convex hull incorporating all 4 points. i.e how to connect the points without having any of them cross each other.
void sortQuadanglePoints(int quadanglePoints[4][2]) 
{
	int pointsInOrder[4][2] = { 0 }; // In order to retain all data about the points while they sort, the program reforms the points in a separate 2D array until they are in order
									// then at the end copies the sorted version into the original variable.
	int pointBuffer[2] = { 0 };

	for (int i = 0; i < 4; i++) // copy the points into the dummy 2D array
	{
		pointsInOrder[i][0] = quadanglePoints[i][0];
		pointsInOrder[i][1] = quadanglePoints[i][1];
	}

	for (int i = 1; i < 4; i++) // This loop will determine which point out of the set is the farthest right (and down) in the plane.
	{
		if (pointsInOrder[i][0] > pointsInOrder[0][0])
		{
			pointBuffer[0] = pointsInOrder[0][0]; // There's a lot of lines here because variables have to be juggled around with a buffer so that they can be swapped without data loss.
			pointBuffer[1] = pointsInOrder[0][1];

			pointsInOrder[0][0] = pointsInOrder[i][0];
			pointsInOrder[0][1] = pointsInOrder[i][1];

			pointsInOrder[i][0] = pointBuffer[0];
			pointsInOrder[i][1] = pointBuffer[1];
		}
		else if ((pointsInOrder[i][0] >= pointsInOrder[0][0]) && (pointsInOrder[i][1] < pointsInOrder[0][1])) // There's a tie for largest x value, so take the lowest y as the next judge.
		{
			pointBuffer[0] = pointsInOrder[0][0];
			pointBuffer[1] = pointsInOrder[0][1];

			pointsInOrder[0][0] = pointsInOrder[i][0];
			pointsInOrder[0][1] = pointsInOrder[i][1];

			pointsInOrder[i][0] = pointBuffer[0];
			pointsInOrder[i][1] = pointBuffer[1];
		}
	}

	double* anglesPtr;
	int angleIndex;
	int adjacentPoint[2];
	double side1, side2, side3, angleBuffer;

	// A Jarvis March takes a point and calculate the angles to all the other points, it then takes the most acute angle and deems that point as the next in the series
	// Effectively this is like starting on the right side of the plane and connecting points counter clockwise until back at the start.
	for (int i = 0; i < 2; i++) // With 4 points you only have to do this twice because the fourth point is figured out by process of elimination.
	{
		adjacentPoint[0] = pointsInOrder[i][0] + 1; // To calculate an angle you need 3 points so this generates a point adjacent in plane to the right of the current point acting as the 'axis'
		adjacentPoint[1] = pointsInOrder[i][1];		// It is used to establish where angle measurements begin (like how the x-axis is generally considered 0 degrees then you wind around counter clockwise)
		angleIndex = 0;
		angleBuffer = 360;
		for (int j = (i + 1); j < 4; j++) // this loop gets smaller and smaller also by process of elimination.
		{
			side1 = 1; // the side between the dummy point shifted to right by 1 unit.
			side2 = calculateLengthBetweenPoints(pointsInOrder[i], pointsInOrder[j]);
			side3 = calculateLengthBetweenPoints(adjacentPoint, pointsInOrder[j]);
			anglesPtr = calculateAngles(side1, side2, side3); // reuse the calculateAngle function (even though it does a bit of extra work by assuming its a triangle and calculate 3 angles)

			if (pointsInOrder[i][1] > pointsInOrder[j][1]) // the angles default to the acute angle as if its an inside angle of a triangle so this converts them to the corresponding obtuse angle if the point its checking lies further down on the y axis than the 'axis' point.
				anglesPtr[2] = 360 - anglesPtr[2];

			else if (anglesPtr[2] < angleBuffer) // A new 'most acute' angle was found and that point is slotted into the sorted array as the next point on the convex hull.
			{
				angleBuffer = anglesPtr[2];

				pointBuffer[0] = pointsInOrder[i + 1][0];
				pointBuffer[1] = pointsInOrder[i + 1][1];

				pointsInOrder[i + 1][0] = pointsInOrder[j][0];
				pointsInOrder[i + 1][1] = pointsInOrder[j][1];

				pointsInOrder[j][0] = pointBuffer[0];
				pointsInOrder[j][1] = pointBuffer[1];
			}
		}
	}

	for (int i = 0; i < 4; i++) // the points are sorted and can now be copied back into the original array
	{
		quadanglePoints[i][0] = pointsInOrder[i][0];
		quadanglePoints[i][1] = pointsInOrder[i][1];
	}

	return;
}

double calculateLengthBetweenPoints(int* point1, int* point2) // straight forward calculation given points on a 2D plane.
{
	double length = 0;

	double deltaX = abs(point1[0] - point2[0]);
	double deltaY = abs(point1[1] - point2[1]);

	length = sqrt(pow(deltaX, 2) + pow(deltaY, 2));

	return length;
}

// Uses the calculateAngles function from triangleSolver.c 
// The calculatesAngle function calculates 3 angles given 3 side lengths but for the quadrilateral only one of those angles will actually be in the shape
double* calculateQuadangleAngles(int quadanglePoints[4][2])
{
	double* angles = malloc(4* sizeof(double));
	double side1, side2, side3;

	for (int i = 0; i < 4; i++)
	{
		if (i == 0)
		{
			side1 = calculateLengthBetweenPoints(quadanglePoints[3], quadanglePoints[i]);
			side2 = calculateLengthBetweenPoints(quadanglePoints[3], quadanglePoints[i + 1]);
			side3 = calculateLengthBetweenPoints(quadanglePoints[i], quadanglePoints[i + 1]);
			angles[i] = *calculateAngles(side2, side1, side3); // points are fed into this funciton in a specific order so that the return array has the important angle as the first element
		}
		else if (i == 3)
		{
			side1 = calculateLengthBetweenPoints(quadanglePoints[i-1], quadanglePoints[i]);
			side2 = calculateLengthBetweenPoints(quadanglePoints[i-1], quadanglePoints[0]);
			side3 = calculateLengthBetweenPoints(quadanglePoints[i], quadanglePoints[0]);
			angles[i] = *calculateAngles(side2, side1, side3);
		}
		else
		{
			side1 = calculateLengthBetweenPoints(quadanglePoints[i - 1], quadanglePoints[i]);
			side2 = calculateLengthBetweenPoints(quadanglePoints[i - 1], quadanglePoints[i + 1]);
			side3 = calculateLengthBetweenPoints(quadanglePoints[i], quadanglePoints[i + 1]);
			angles[i] = *calculateAngles(side2, side1, side3);
		}
	}

	return angles;
}

double calculateArea(int quadanglePoints[4][2]) // straightforward area calculation for a rectangle
{
	double length = calculateLengthBetweenPoints(quadanglePoints[2], quadanglePoints[3]);
	double width = calculateLengthBetweenPoints(quadanglePoints[2], quadanglePoints[1]);

	double area = length * width;

	return area;
}

double calculatePerimeter(int quadanglePoints[4][2]) // straightforward perimeter calculation given 4 points in coordinate form.
{
	double side1 = calculateLengthBetweenPoints(quadanglePoints[0], quadanglePoints[1]);
	double side2 = calculateLengthBetweenPoints(quadanglePoints[1], quadanglePoints[2]);
	double side3 = calculateLengthBetweenPoints(quadanglePoints[2], quadanglePoints[3]);
	double side4 = calculateLengthBetweenPoints(quadanglePoints[3], quadanglePoints[0]);

	double perimeter = side1 + side2 + side3 + side4;

	return perimeter;
}