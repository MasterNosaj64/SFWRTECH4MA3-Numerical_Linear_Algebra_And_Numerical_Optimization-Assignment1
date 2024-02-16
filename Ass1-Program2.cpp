/*
File:Ass1.cpp
Author: Jason Waid | 400424500
McMaster University | Numerical Linear Algebra and Numerical Optimization | SFWRTECH 4MA3
Professor: SESHASAI SRINIVASAN 
Description: Implementation of Gaussian Elimination with & without Partial Pivoting
*/

#include <iostream>
#include <ios>
#include <limits>
#include <string>
#include <algorithm>
#include <iterator>
#include <utility>

using namespace std;

void displayGreeting();
void displayMenu();
bool checkInputInt(string inputBuffer);
bool checkInputDouble(string inputBuffer);
int getNumUnknowns(string inputBuffer);
void getFactorsDisplay(string inputBuffer, int numUnknowns, double matrix[][11]);
double getFactorConstant(string inputBuffer, int unknownNum);
double getFactorB(string inputBuffer);
void clearInputBuffer();
void printMatrix(double matrix[][11], int numUnknowns);
void performGaussianEliminationWithPartialPivoting(double matrix[][11], int numUnknowns);
void performGaussianElimination(double matrix[][11], int numUnknowns);
void displayTransformedMatrixMessage();
void displayInitialMatrixMessage();
void performBackwardsSubstitution(double matrix[][11], double unknownVals[10], int numUnknowns);
void displayUnknownValuesMessage();
void displayUnknownValues(double unknownVals[10], int numUnknowns);
void displayMatrixModificationMessage(double matrix[][11], int j, int k, double ratio);
void displayMatrixSwapMessage(int row1, int row2);

/*
Function: displayGreeting
Purpose: Greeting message intended for app launch
Return: none
Author: Jason Waid
Date Modified: 02/05/2022
*/
void displayGreeting() {
	cout << "Welcome to Assignment 1!\n";
	cout << "Developed by Jason Waid\n";
}

/*
Function: displayMenu
Purpose: Menu for Gaussian Elimination method
Return: none
Author: Jason Waid
Date Modified: 02/09/2022
*/
void displayMenu() {
	cout << "Choose a program:\n";
	cout << "1: Gaussian Elimination\n";
	cout << "2: Gaussian Elimination with Partial Pivoting\n";
}

/*
Function: checkInputInt
Purpose: Validates Input String by checking if it is a Number
Param: a input buffer of type string
Return: Boolean depending on success or failure
Author: Jason Waid
Date Modified: 02/05/2022
*/
bool checkInputInt(string inputBuffer) {

	//check for negative val
	if (!strcmp(inputBuffer.substr(0, 1).c_str(), "-")) {
		cout << inputBuffer.c_str() << " is not valid!\n";
		clearInputBuffer();
		return false;
	}

	for (char const& c : inputBuffer) {

		if (isdigit(c) == 0) {
			cout << inputBuffer.c_str() << " is not valid!\n";
			clearInputBuffer();
			return false;
		}	

	}
	if (stoi(inputBuffer) > 0 && stoi(inputBuffer) <= 10) {
		return true;
	}
	else {
		cout << inputBuffer.c_str() << " is not valid!\n";
		clearInputBuffer();
		return false;
	}
}

/*
Function: checkInputMenu
Purpose: Validates Input String by checking if it is a valid Number
Param: a input buffer of type string
Return: Boolean depending on success or failure
Author: Jason Waid
Date Modified: 02/05/2022
*/
bool checkInputMenu(string inputBuffer) {

	//check for negative val
	if (!strcmp(inputBuffer.substr(0, 1).c_str(), "-")) {
		cout << inputBuffer.c_str() << " is not valid!\n";
		clearInputBuffer();
		return false;
	}
	for (char const& c : inputBuffer) {
		if (isdigit(c) == 0) {
			cout << inputBuffer.c_str() << " is not valid!\n";
			clearInputBuffer();
			return false;
		}
	}
	if (stoi(inputBuffer) == 1 || stoi(inputBuffer) == 2) {
		return true;
	}
	else {
		cout << inputBuffer.c_str() << " is not valid!\n";
		clearInputBuffer();
		return false;
	}
}

/*
Function: checkInputDouble
Purpose: Validates Input String by checking if it is a Number
Param: a input buffer of type string
Return: Boolean depending on success or failure
Author: Jason Waid
Date Modified: 02/05/2022
*/
bool checkInputDouble(string inputBuffer) {
	bool negativeCheck = false;
	if (!strcmp(inputBuffer.substr(0, 1).c_str(), "-")) {
		inputBuffer.erase(0);
		negativeCheck = true;

	}

	for (char const& c : inputBuffer) {
		if (isdigit(c) == 0) {
			cout << inputBuffer.c_str() << " is not valid!\n";
			clearInputBuffer();
			return false;
		}
	}
	if (negativeCheck == true) {
		inputBuffer.insert(0, "-");
	}
	return true;
}

/*
Function: getMenuOption
Purpose: Gets input from user for number of desired unknowns
Param: a input buffer of type string
Return: Integer value entered
Author: Jason Waid
Date Modified: 02/05/2022
*/
int getMenuOption(string inputBuffer) {
	do {
		cin >> inputBuffer;
	} while (!checkInputMenu(inputBuffer));
	return atoi(inputBuffer.c_str());
}

/*
Function: getNumUnknowns
Purpose: Gets input from user for number of desired unknowns
Param: a input buffer of type string
Return: Integer value entered
Author: Jason Waid
Date Modified: 02/05/2022
*/
int getNumUnknowns(string inputBuffer) {
	do {
		cout << "Enter number of unknowns (max is 10): ";
		cin >> inputBuffer;
	} while (!checkInputInt(inputBuffer));
	return atoi(inputBuffer.c_str());
}


/*
Function: getFactorsDisplay
Purpose: Prompts user for input for factor values
Param: a input buffer of type string
Return: Integer value entered
Author: Jason Waid
Date Modified: 02/06/2022
*/
void getFactorsDisplay(string inputBuffer, int numUnknowns, double matrix[][11]) {
	for (int i = 0; i < numUnknowns; i++) {
		cout << "Now entering Equation " << i + 1 << "\n";
		for (int k = 1; k <= numUnknowns; k++) {

			if (k == 1) {
				cout << "?x" << k;
			}
			else
				cout << " + ?x" << k;
		}
		cout << " = b\n";

		for (int j = 0; j < numUnknowns; j++) {
			matrix[i][j] = getFactorConstant(inputBuffer, j);
			clearInputBuffer();
		}
		matrix[i][numUnknowns] = getFactorB(inputBuffer);
		clearInputBuffer();
	}
}

/*
Function: getFactorConstant
Purpose: Gets the Constant multiplying xi
Param: inputBuffer which is users input, unknownNum which is count of xi
Return: Double conversion of inputBuffer after validation is passed
Author: Jason Waid
Date Modified: 02/05/2022
*/
double getFactorConstant(string inputBuffer, int unknownNum) {
	do {
		cout << "Enter constant for x" << unknownNum + 1 << ": ";
		cin >> inputBuffer;
	} while (!checkInputDouble(inputBuffer));
	return stod(inputBuffer);
}

/*
Function: getFactorB
Purpose: Gets the value of b
Param: inputBuffer, which is the users input
Return: Double conversion of inputBuffer after validation is passed
Author: Jason Waid
Date Modified: 02/09/2022
*/
double getFactorB(string inputBuffer) {
	do {
		cout << "Enter value for b: ";
		cin >> inputBuffer;
	} while (!checkInputDouble(inputBuffer));
	return stod(inputBuffer);
}

/*
Function: clearInputBuffer
Purpose: clears the input buffer.
Param: NONE
Return: NONE
Author: Jason Waid
Date Modified: 02/05/2022
*/
void clearInputBuffer() {
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

/*
Function: printMatrix
Purpose: prints the matrix
Param: double matrix[][11] which is the matrix in question, int numRows which are the number of rows, int numColumns which are the number of columns
Return: NONE
Author: Jason Waid
Date Modified: 02/06/2022
*/
void printMatrix(double matrix[][11], int numUnknowns) {

	for (int i = 0; i < numUnknowns; i++) {
		for (int j = 0; j < numUnknowns; j++) {
			cout << matrix[i][j] << "\t";
		}
		cout << "|\t" << matrix[i][numUnknowns] << "\n";
	}
	cout << "\n";
}

/*
Function: performGaussianEliminationWithPartialPivoting
Purpose: Performs Gaussian Elimination using partial pivoting on the matrix
Param: double matrix[][11] which is the matrix in question, int numRows which are the number of rows, int numColumns which are the number of columns
Return: NONE
Author: Jason Waid
Date Modified: 02/09/2022
*/
void performGaussianEliminationWithPartialPivoting(double matrix[][11], int numUnknowns) {

	int p = 0;
	double maxPivot = 0;
	double ratio = 0;
	//k = column
	for (int k = 0; k < numUnknowns - 1; k++) {
		maxPivot = 0;
		p = k;
		//search for largest val for pivot
		//i = row
		for(int i = k; i < numUnknowns; i++){
			if (fabs(matrix[i][k]) > maxPivot) {
				maxPivot = fabs(matrix[i][k]);
				p = i;
			}
		}
		if (p != k) {
			displayMatrixSwapMessage(p, k);
			//p|k = row
			//i = column
			for (int i = k; i < numUnknowns+1; i++) {
				swap(matrix[p][i], matrix[k][i]);
			}
			printMatrix(matrix, numUnknowns);
		}
		if (matrix[k][k] == 0) {
			//skip this iteration
		}
		else {
			//j = row
			//k = column
			for (int j = k+1; j < numUnknowns; j++) {
				ratio = matrix[j][k] / matrix[k][k];
				displayMatrixModificationMessage(matrix, j, k, ratio);

				for (int i = k; i < numUnknowns+1; i++) {
					matrix[j][i] = matrix[j][i] - (ratio * matrix[k][i]);
				}
				printMatrix(matrix, numUnknowns);
			}
		}
	}
}

/*
Function: performGaussianElimination
Purpose: Performs Gaussian Elimination on the matrix
Param: double matrix[][11] which is the matrix in question, int numRows which are the number of rows, int numColumns which are the number of columns
Return: NONE
Author: Jason Waid
Date Modified: 02/09/2022
*/
void performGaussianElimination(double matrix[][11], int numUnknowns) {
	double ratio = 0;
	for (int k = 0; k < numUnknowns - 1; k++) {
		if (matrix[k][k] == 0) {
			//stop
			exit(0);
		}
		for (int j = k + 1; j < numUnknowns; j++) {
			ratio = matrix[j][k] / matrix[k][k];
			displayMatrixModificationMessage(matrix, j, k, ratio);

			for (int i = k; i < numUnknowns + 1; i++) {
				matrix[j][i] = matrix[j][i] - (ratio * matrix[k][i]);
			}
			printMatrix(matrix, numUnknowns);
		}
	}
}

/*
Function: displayTransformedMatrixMessage
Purpose: Displays header for transfomred matrix
Param: NONE
Return: NONE
Author: Jason Waid
Date Modified: 02/06/2022
*/
void displayTransformedMatrixMessage() {
	cout << "Transformed Matrix\n";
	cout << "--------------------------------------------\n";
}

/*
Function: displayMatrixSwapMessage
Purpose: Displays header for matrix row swaping
Param: int row1: first row, int row2: second row
Return: NONE
Author: Jason Waid
Date Modified: 02/09/2022
*/
void displayMatrixSwapMessage(int row1, int row2) {
	cout << "Swapping row " << row1 + 1 << " for row " << row2 + 1 << "\n";
	cout << "--------------------------------------------\n";
}

/*
Function: displayMatrixModificationMessage
Purpose: Displays header for modifying matrix
Param: double matrix: the matrix, int j: row to be modified, int k: sample row, double ratio: the ratio to multiply the element by
Return: NONE
Author: Jason Waid
Date Modified: 02/09/2022
*/
void displayMatrixModificationMessage(double matrix[][11], int j, int k, double ratio) {
	cout << "Ratio: " << matrix[j][k] << " / " << matrix[k][k] << " = " << ratio << "\n";
	cout << "Modifying Matrix: R" << j + 1 << " = R" << j + 1 << " - " << ratio << "R" << k + 1 << "\n";
	cout << "--------------------------------------------\n";
}

/*
Function: displayInitialMatrixMessage
Purpose: Displays header for initial matrix
Param: NONE
Return: NONE
Author: Jason Waid
Date Modified: 02/06/2022
*/
void displayInitialMatrixMessage() {
	cout << "Initial Matrix\n";
	cout << "--------------------------------------------\n";
}


/*
Function: performBackwardsSubstitution
Purpose: Performs backwards substituion on the matrix
Param: double matrix[][] which is the matrix in question, double unknownVals[10] which is arroy for storing the unknowns, int numUnknowns is the number of unknowns
Return: NONE
Author: Jason Waid
Date Modified: 02/09/2022
*/
void performBackwardsSubstitution(double matrix[][11], double unknownVals[10], int numUnknowns) {

	double temp = 0;

	for (int i = numUnknowns - 1; i >= 0; i--)
	{
		temp = 0;
		for (int j = i + 1; j < numUnknowns; j++) {
			temp += matrix[i][j] * unknownVals[j];
		}
		unknownVals[i] = (matrix[i][numUnknowns] - temp) / matrix[i][i];
	}
}

/*
Function: displayUnknownValuesHeader
Purpose: Displays header for value of unknowns
Param: NONE
Return: NONE
Author: Jason Waid
Date Modified: 02/06/2022
*/
void displayUnknownValuesMessage() {
	cout << "Value of Unknowns\n";
	cout << "--------------------------------------------\n";
}

/*
Function: displayUnknownValues
Purpose: Displays value of unknowns
Param: NONE
Return: NONE
Author: Jason Waid
Date Modified: 02/06/2022
*/
void displayUnknownValues(double unknownVals[10], int numUnknowns) {
	for (int i = 0; i < numUnknowns; i++) {
		cout << "x" << i + 1 << "= " << unknownVals[i] << "\n";
	}
}

int main()
{
	string inputBuffer;
	int numUnknowns = 0;
	int menu = 0;
	double matrix[10][10 + 1] = {};
	double unknownVals[10] = {};


	displayGreeting();
	displayMenu();
	menu = getMenuOption(inputBuffer);
	clearInputBuffer();

	numUnknowns = getNumUnknowns(inputBuffer);
	clearInputBuffer();

	getFactorsDisplay(inputBuffer, numUnknowns, matrix);

	displayInitialMatrixMessage();
	printMatrix(matrix, numUnknowns);

	if (menu == 1) {
		performGaussianElimination(matrix, numUnknowns);
	}
	else if (menu == 2) {
		performGaussianEliminationWithPartialPivoting(matrix, numUnknowns);
	}
	
	displayTransformedMatrixMessage();
	printMatrix(matrix, numUnknowns);
	performBackwardsSubstitution(matrix, unknownVals, numUnknowns);
	displayUnknownValuesMessage();
	displayUnknownValues(unknownVals, numUnknowns);

	return 0;
}