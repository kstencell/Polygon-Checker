#include "pch.h"
#include "CppUnitTest.h"

extern "C"
{
#include "main.h"
#include "triangleSolver.h"
#include "quadangleSolver.h"
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PolygonCheckerTests
{
	TEST_CLASS(PolygonCheckerTests)
	{
	public:
		// ------------------------- //
		// ***** TRIANGLE CHECKS**** //
		// ------------------------- //
		TEST_METHOD(T01_analyzeTriangle_0_0_0_NotATriangle)
		{
			//Arrange
			char* result = "";

			//Act
			result = analyzeTriangle(0, 0, 0);

			//Assert
			Assert::AreEqual("Not a triangle", result);
		}
		TEST_METHOD(T02_analyzeTriangle_0_1_1_NotATriangle)
		{
			//Arrange
			char* result = "";

			//Act
			result = analyzeTriangle(0, 1, 1);

			//Assert
			Assert::AreEqual("Not a triangle", result);
		}
		TEST_METHOD(T03_analyzeTriangle_0_0_1_NotATriangle)
		{
			//Arrange
			char* result = "";

			//Act
			result = analyzeTriangle(0, 0, 1);

			//Assert
			Assert::AreEqual("Not a triangle", result);
		}
		TEST_METHOD(T04_analyzeTriangle_1_1_1_Equilateral)
		{
			//Arrange
			char* result = "";

			//Act
			result = analyzeTriangle(1, 1, 1);

			//Assert
			Assert::AreEqual("Equilateral triangle", result);
		}
		TEST_METHOD(T05_analyzeTriangle_2_2_3_Isosceles)
		{
			//Arrange
			char* result = "";

			//Act
			result = analyzeTriangle(2, 2, 3);

			//Assert
			Assert::AreEqual("Isosceles triangle", result);
		}
		TEST_METHOD(T06_analyzeTriangle_2_3_4_Scalene)
		{
			//Arrange
			char* result = "";

			//Act
			result = analyzeTriangle(2, 3, 4);

			//Assert
			Assert::AreEqual("Scalene triangle", result);
		}
		TEST_METHOD(T07_analyzeTriangle_1_1_2_NotATriangle)
		{
			//Arrange
			char* result = "";

			//Act
			result = analyzeTriangle(1, 1, 2);

			//Assert
			Assert::AreEqual("Not a triangle", result);
		}
		TEST_METHOD(T08_analyzeTriangle_1_2_1_NotATriangle)
		{
			//Arrange
			char* result = "";

			//Act
			result = analyzeTriangle(1, 2, 1);

			//Assert
			Assert::AreEqual("Not a triangle", result);
		}
		TEST_METHOD(T09_analyzeTriangle_2_1_1_NotATriangle)
		{
			//Arrange
			char* result = "";

			//Act
			result = analyzeTriangle(2, 1, 1);

			//Assert
			Assert::AreEqual("Not a triangle", result);
		}
		TEST_METHOD(T10_analyzeTriangle_1_10_10_Isosceles)
		{
			//Arrange
			char* result = "";

			//Act
			result = analyzeTriangle(1, 10, 10);

			//Assert
			Assert::AreEqual("Isosceles triangle", result);
		}
		TEST_METHOD(T11_analyzeTriangle_999999999999_10_10_NotATriangle)
		{
			//Arrange
			char* result = "";

			//Act
			result = analyzeTriangle(999999999999, 10, 10);

			//Assert
			Assert::AreEqual("Not a triangle", result);
		}
		TEST_METHOD(T12_checkValidDimensions_3_4_5_true)
		{
			//Arrange
			int side1 = 3;
			int side2 = 4;
			int side3 = 5;
			bool areDimensionsValid;

			//Act
			areDimensionsValid = checkValidDimensions(side1, side2, side3);


			//Assert
			Assert::AreEqual(true, areDimensionsValid);
		}
		TEST_METHOD(T13_checkValidDimensions_neg1_4_5_true)
		{
			//Arrange
			int side1 = -1;
			int side2 = 4;
			int side3 = 5;
			bool areDimensionsValid;

			//Act
			areDimensionsValid = checkValidDimensions(side1, side2, side3);


			//Assert
			Assert::AreEqual(false, areDimensionsValid);
		}
		TEST_METHOD(T14_calculateAngles_3_4_5_37_53_90)
		{
			//Arrange
			double* resultPtr;
			double angle1, angle2, angle3;

			//Act
			resultPtr = calculateAngles(3,4,5);
			angle1 = round(resultPtr[0]);
			angle2 = round(resultPtr[1]);
			angle3 = round(resultPtr[2]);

			//Assert
			Assert::AreEqual(37.0, angle1);
			Assert::AreEqual(53.0, angle2);
			Assert::AreEqual(90.0, angle3);
		}
		TEST_METHOD(T15_calculateAngles_2_3_4_29_47_105)
		{
			//Arrange
			double* resultPtr;
			double angle1, angle2, angle3;

			//Act
			resultPtr = calculateAngles(2, 3, 4);
			angle1 = round(resultPtr[0]);
			angle2 = round(resultPtr[1]);
			angle3 = round(resultPtr[2]);

			//Assert
			Assert::AreEqual(29.0, angle1);
			Assert::AreEqual(47.0, angle2);
			Assert::AreEqual(104.0, angle3);
		}
		TEST_METHOD(T16_calculateAngles_3_2_4_47)
		{
			//Arrange
			double* resultPtr;
			double angle1, angle2, angle3;

			//Act
			resultPtr = calculateAngles(3, 2, 4);
			angle1 = round(resultPtr[0]);

			//Assert
			Assert::AreEqual(47.0, angle1);
		}

		// ------------------------------ //
		// ***** QUADRILATERAL CHECKS**** //
		// ------------------------------ //
		TEST_METHOD(T17_sortQuadanglePoints_x1y1_x0y0_x1y0_x0y1_true)
		{
			//Arrange
			int quadanglePoints[4][2] = { 0 };
			int i = 0;
			int pointParameters[] = { 1,1,0,0,1,0,0,1 };
			int pointsInOrder[] = { 1,0,1,1,0,1,0,0 };

			for (int x = 0; x < 4; x++)
			{
				for (int y = 0; y < 2; y++)
				{
					quadanglePoints[x][y] = pointParameters[i];
					i++;
				}
			}
			i = 0;

			//Act
			sortQuadanglePoints(quadanglePoints);


			//Assert
			for (int x = 0; x < 4; x++)
			{
				for (int y = 0; y < 2; y++)
				{
					Assert::AreEqual(pointsInOrder[i], quadanglePoints[x][y]);
					i++;
				}
			}
		}
		TEST_METHOD(T18_sortQuadanglePoints_x10y1_xneg5y18_x0y0_x3y7_true)
		{
			//Arrange
			int quadanglePoints[4][2] = { 0 };
			int i = 0;
			int pointParameters[] = { 10,1,-5,18,0,0,3,7 };
			int pointsInOrder[] = { 10,1,-5,18,0,0,3,7 };

			for (int x = 0; x < 4; x++)
			{
				for (int y = 0; y < 2; y++)
				{
					quadanglePoints[x][y] = pointParameters[i];
					i++;
				}
			}
			i = 0;

			//Act
			sortQuadanglePoints(quadanglePoints);


			//Assert
			for (int x = 0; x < 4; x++)
			{
				for (int y = 0; y < 2; y++)
				{
					Assert::AreEqual(pointsInOrder[i], quadanglePoints[x][y]);
					i++;
				}
			}
		}
		TEST_METHOD(T19_sortQuadanglePoints_x24y7_x3y17_x32y2_x7y56_true)
		{
			//Arrange
			int quadanglePoints[4][2] = { 0 };
			int i = 0;
			int pointParameters[] = { 24,7,3,17,32,2,7,56 };
			int pointsInOrder[] = { 32,2,7,56,3,17,24,7 };

			for (int x = 0; x < 4; x++)
			{
				for (int y = 0; y < 2; y++)
				{
					quadanglePoints[x][y] = pointParameters[i];
					i++;
				}
			}
			i = 0;

			//Act
			sortQuadanglePoints(quadanglePoints);


			//Assert
			for (int x = 0; x < 4; x++)
			{
				for (int y = 0; y < 2; y++)
				{
					Assert::AreEqual(pointsInOrder[i], quadanglePoints[x][y]);
					i++;
				}
			}
		}
		TEST_METHOD(T20_calculateLengthBetweenPoints_x0y0_x3y4_5)
		{
			//Arrange
			int point1[2] = { 0,0 };
			int point2[2] = { 3,4 };
			int* p_point1 = point1;
			int* p_point2 = point2;
			int i=0;
			double length;

			//Act
			length = calculateLengthBetweenPoints(p_point1, p_point2);

			//Assert
			Assert::AreEqual(5.0, length);
		}
		TEST_METHOD(T21_calculateLengthBetweenPoints_xneg5y6_x10yneg11_5)
		{
			//Arrange
			int point1[2] = { -5,6 };
			int point2[2] = { 10,-11 };
			int* p_point1 = point1;
			int* p_point2 = point2;
			int i = 0;
			double length;

			//Act
			length = round(calculateLengthBetweenPoints(p_point1, p_point2));

			//Assert
			Assert::AreEqual(23.0, length);
		}
		TEST_METHOD(T22_calculateQuadangleAngles_x32y2_x7y58_x3y17_x24y7_33_31_110_173)
		{
			//Arrange
			int quadanglePoints[4][2];
			int pointParameters[] = { 32,2,7,56,3,17,24,7 };
			double angles[] = {33.0, 31.0, 110.0, 173.0};
			int i = 0;
			double* quadangleAnglesPtr;

			for (int x = 0; x < 4; x++)
			{
				for (int y = 0; y < 2; y++)
				{
					quadanglePoints[x][y] = pointParameters[i];
					i++;
				}
			}

			//Act
			quadangleAnglesPtr = calculateQuadangleAngles(quadanglePoints);

			//Assert
			for (int i = 0; i < 4; i++)
			{
				Assert::AreEqual(angles[i], round(quadangleAnglesPtr[i]));
			}
		}
		TEST_METHOD(T23_calculateQuadangleAngles_x10y1_xneg5y18_x0y0_x3y7_8_26_39_73)
		{
			//Arrange
			int quadanglePoints[4][2];
			int pointParameters[] = { 10,1,-5,18,0,0,3,7 };
			double angles[] = { 8.0, 26.0, 39.0, 73.0 };
			int i = 0;
			double* quadangleAnglesPtr;

			for (int x = 0; x < 4; x++)
			{
				for (int y = 0; y < 2; y++)
				{
					quadanglePoints[x][y] = pointParameters[i];
					i++;
				}
			}

			//Act
			quadangleAnglesPtr = calculateQuadangleAngles(quadanglePoints);

			//Assert
			for (int i = 0; i < 4; i++)
			{
				Assert::AreEqual(angles[i], round(quadangleAnglesPtr[i]));
			}
		}
		TEST_METHOD(T24_calculateArea_x1y0_x1y1_x0y1_x0y0_1)
		{
			//Arrange
			int quadanglePoints[4][2];
			int pointParameters[] = { 1,0,1,1,1,0,0,0 };
			int i = 0;
			double area;

			for (int x = 0; x < 4; x++)
			{
				for (int y = 0; y < 2; y++)
				{
					quadanglePoints[x][y] = pointParameters[i];
					i++;
				}
			}

			//Act
			area = calculateArea(quadanglePoints);

			//Assert
			for (int i = 0; i < 4; i++)
			{
				Assert::AreEqual(1.0, area);
			}
		}
		TEST_METHOD(T25_calculateArea_x5y0_x5y3_x0y3_x0y0_15)
		{
			//Arrange
			int quadanglePoints[4][2];
			int pointParameters[] = { 5,0,5,3,0,3,0,0 };
			int i = 0;
			double area;

			for (int x = 0; x < 4; x++)
			{
				for (int y = 0; y < 2; y++)
				{
					quadanglePoints[x][y] = pointParameters[i];
					i++;
				}
			}

			//Act
			area = calculateArea(quadanglePoints);

			//Assert
			for (int i = 0; i < 4; i++)
			{
				Assert::AreEqual(15.0, area);
			}
		}
		TEST_METHOD(T26_calculatePerimeter_x5y0_x5y3_x0y3_x0y0_15)
		{
			//Arrange
			int quadanglePoints[4][2];
			int pointParameters[] = { 5,0,5,3,0,3,0,0 };
			int i = 0;
			double perimeter;

			for (int x = 0; x < 4; x++)
			{
				for (int y = 0; y < 2; y++)
				{
					quadanglePoints[x][y] = pointParameters[i];
					i++;
				}
			}

			//Act
			perimeter = calculatePerimeter(quadanglePoints);

			//Assert
			for (int i = 0; i < 4; i++)
			{
				Assert::AreEqual(16.0, perimeter);
			}
		}
		TEST_METHOD(T27_calculatePerimeter_x1y0_x1y1_x0y1_x0y0_1)
		{
			//Arrange
			int quadanglePoints[4][2];
			int pointParameters[] = { 1,0,1,1,0,1,0,0 };
			int i = 0;
			double perimeter;

			for (int x = 0; x < 4; x++)
			{
				for (int y = 0; y < 2; y++)
				{
					quadanglePoints[x][y] = pointParameters[i];
					i++;
				}
			}

			//Act
			perimeter = calculatePerimeter(quadanglePoints);

			//Assert
			for (int i = 0; i < 4; i++)
			{
				Assert::AreEqual(4.0, perimeter);
			}
		}
	};
}
