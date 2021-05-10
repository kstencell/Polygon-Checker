//
// Group Assignment
// CSCN71020 - F20
// Karl Stencell, Thomas Horvath, Gautam Singh - Dec 2020
//
// REVISION HISTORY
// 1.0		2020-Dec-14		initial
//
// VERSION 1.0 NOTES
// Header file for quadangleSolver.c

#pragma once

#include <stdbool.h>

// PROTOTYPES
void sortQuadanglePoints(int quadanglePoints[4][2]);
double calculateLengthBetweenPoints(int*, int*);
double* calculateQuadangleAngles(int quadanglePoints[4][2]);
double calculateArea(int quadanglePoints[4][2]);
double calculatePerimeter(int quadanglePoints[4][2]);
