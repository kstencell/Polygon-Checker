//
// Group Assignment
// CSCN71020 - F20
// Karl Stencell, Thomas Horvath, Gautam Singh - Dec 2020
//
// REVISION HISTORY
// 1.0		2020-Nov-26		initial
//
// VERSION 1.0 NOTES
// Header file for main.c

#pragma once

#define BUFFER_SIZE		11

// PROTOTYPES
void printWelcome();
int printShapeMenu();

void triangleSelected(void);
double* getTriangleSides(double* triangleSides);

void quadangleSelected(void);
void getQuadanglePoints(int quadanglePoints[4][2]);

double getNumberFromUser(void);