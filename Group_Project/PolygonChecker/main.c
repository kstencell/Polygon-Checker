//
// Group Assignment
// CSCN71020 - F20
// Karl Stencell, Thomas Horvath, Gautam Singh - Dec 2020
//
// REVISION HISTORY
// 1.0		2020-Nov-26		initial
//
// VERSION 1.0 NOTES
// This file contains all the functionality needed by the main menu of the program and dealing with user input, and outputting results.. It will print the menu, prompt the user for input to
// declare their option choice, then call the appropriate functions to perform the task the user is trying to accomplish.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "main.h"
#include "triangleSolver.h"
#include "quadangleSolver.h"


int main() {
	bool continueProgram = true;

	while (continueProgram) // main engine of the program to keep driving the program in circles until the user terminates.
	{
		printWelcome();

		int shapeChoice = printShapeMenu();

		switch (shapeChoice)
		{
		case 1:
			printf_s("\nTriangle selected.\n");
			triangleSelected();

			break;
		case 2:
			printf_s("\nQuadrilateral selected.\n");
			quadangleSelected();
			
			break;
		case 3:
			continueProgram = false;
			break;
		default:
			printf_s("\nInvalid value entered.\n");
			break;
		}
	}
	return 0;
}

void printWelcome() {
	printf_s("\n");
	printf_s(" **********************\n");
	printf_s("**     Welcome to     **\n");
	printf_s("**   Polygon Checker  **\n");
	printf_s(" **********************\n");
}

int printShapeMenu() {
	printf_s("1. Triangle\n");
	printf_s("2. Quadrilateral\n");
	printf_s("3. Exit\n");
	printf_s("Enter number: ");

	char userInput[BUFFER_SIZE];
	int optionChoice;

	while (true) // loop to continue to reprompt the user until they terminate the program. Great at catching invalid inputs.
	{
		fgets(userInput, BUFFER_SIZE, stdin);
		userInput[strcspn(userInput, "\n")] = 0;

		if (strcmp("1", userInput) || strcmp("2", userInput) || strcmp("3", userInput))
		{
			optionChoice = atoi(userInput);
			return optionChoice;
		}
		else
			printf_s("Not a valid option, please try again.\n");
	}
}

void triangleSelected() // Runs through all functions/logic associated with triangle functionality in this program.
{
	double triangleSides[3] = { 0, 0, 0 };
	double* triangleSidesPtr;

	triangleSidesPtr = getTriangleSides(triangleSides);
	char* result = analyzeTriangle(triangleSidesPtr[0], triangleSidesPtr[1], triangleSidesPtr[2]); // This will determine if the triangle is legit or not.
	printf_s("\n%s\n", result);

	if (strcmp(result, "Not a triangle")) // Angle calculations wont make sense if the sides don't form a triangle.
	{
		double* triangleAnglesPtr;
		triangleAnglesPtr = calculateAngles(triangleSidesPtr[0], triangleSidesPtr[1], triangleSidesPtr[2]);
		printf_s("\nThe angles of the triangle are %.1f, %.1f, and %.1f degrees\n", triangleAnglesPtr[0], triangleAnglesPtr[1], triangleAnglesPtr[2]);
		free(triangleAnglesPtr); // Memory management.
	}

	return;
}

double* getTriangleSides(double* triangleSides) // get user input for side lengths of a triangle.
{
	char buffer[BUFFER_SIZE];
	bool validInput;
	int stringLength;

	for (int i = 0; i < 3; i++)
	{
		printf_s("\nEnter the length of a side %d: ", i + 1);
		triangleSides[i] = getNumberFromUser();
	}

	return triangleSides;
}

void quadangleSelected() // Runs through all functions/logic associated with quadangle functionality in this program
{
	int quadanglePoints[4][2] = { 0 };

	getQuadanglePoints(quadanglePoints);
	
	sortQuadanglePoints(quadanglePoints); // sorts them in an order that creates a convex hull when linked 1 to 2, 2 to 3, 3 to 4, and 4 back to 1.
	double* quadangleAnglesPtr;
	quadangleAnglesPtr = calculateQuadangleAngles(quadanglePoints); // Calculates all 4 inner angles of the quadrilateral shape
	bool validQuadangle = true;
	bool quadIsRectangle = true;
	for (int i = 0; i < 4; i++) // validation checking to make sure the points are indeed vertices of a quadrilateral shape.
	{
		if ((int)quadangleAnglesPtr[i] == 180 || (int)quadangleAnglesPtr[i] == 0) // if one angle is 0 or 180 then then 3 points are in a line (which actually makes a triangle!)
			validQuadangle = false;

		if ((int)quadangleAnglesPtr[i] != 90) // A check for if the quadrilateral is a rectangle
			quadIsRectangle = false;
	}
	if (!validQuadangle) // go no further if the points aren't good
	{
		printf_s("\nThe points given do not constitute a valid quadrilateral.\n");
	}
	else if (quadIsRectangle) // specific output for rectangles (strings and also AREA)
	{
		printf_s("\nThe points given construct a rectangle!\n");
		printf_s("\nThe angles of the rectangle are all 90 degrees\n"); // Still prints the angles of the quadrilateral, its just a trivial case.
		double area = calculateArea(quadanglePoints);
		printf_s("\nThe area of the rectangle is %.1f units squared.\n", area);
		double perimeter = calculatePerimeter(quadanglePoints);
		printf_s("\nThe perimeter of the rectangle is %.1f units long.\n", perimeter);
	}
	else // an arbitrary quadrilateral shape was formed with the points
	{
		double perimeter = calculatePerimeter(quadanglePoints); // can also get the perimeter easily
		printf_s("\nThe angles of the quadrilateral are %.1f, %.1f, %.1f, and %.1f degrees\n", quadangleAnglesPtr[0], quadangleAnglesPtr[1], quadangleAnglesPtr[2], quadangleAnglesPtr[3]);
		printf_s("\nThe perimeter of the quadrilateral is %.1f units long.\n", perimeter);
	}
}

void getQuadanglePoints(int quadanglePoints[4][2]) // Grabs coordinates for 4 points from the user.
{
	for (int i = 0; i < 4; i++)
	{
		printf("\nFor point #%d:\n", i+1);
		printf("Enter the x value: ");
		quadanglePoints[i][0] = getNumberFromUser();
		printf("Enter the y value: ");
		quadanglePoints[i][1] = getNumberFromUser();
	}
}

double getNumberFromUser() // General purpose function to get input from the user and only pass it along if its in a valid numerical format
{							// This function is used any time user input is requested.
	char buffer[BUFFER_SIZE];
	bool validInput;
	int stringLength;

	do // Loop to keep reprompting the user to enter input until acceptable input is detected.
	{
		validInput = true;
		fgets(buffer, BUFFER_SIZE, stdin);
		stringLength = strlen(buffer);
		if (!strcmp(buffer, "\n"))
			validInput = false;
		else
			buffer[stringLength - 1] = '\0';
		for (int j = 0; j < stringLength - 1; j++)
		{
			if (!isdigit(buffer[j])) // To accept only numerical digits in the user input
				validInput = false;
			if (j == 0 && buffer[0] == '-' && stringLength > 2) // To accept negative numbers for input.
				validInput = true;
		}
		if (stringLength >= 10) // Ints at max are 9 digits
			validInput = false;
		if (!validInput)
			printf_s("\nNot a valid input. Please try again.\n\n");
	} while (!validInput);

	return (double)atoi(buffer);
}