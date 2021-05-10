//
// Group Assignment
// CSCN71020 - F20
// Karl Stencell, Thomas Horvath, Gautam Singh - Dec 2020
//
// REVISION HISTORY
// 1.0		2020-Nov-26		initial
//
// VERSION 1.0 NOTES
// Header file for triangleSolver.c

#pragma once
#include <math.h>
#include <stdbool.h>

#define PI acos(-1.0)

// PROTOTYPES
char* analyzeTriangle(int side1, int side2, int side3);
double* calculateAngles(double, double, double);
bool checkValidDimensions(int, int, int);