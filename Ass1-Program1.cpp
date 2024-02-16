#include <iostream>
#include <ios>
#include <limits>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

void displayGreeting();
bool checkInputInt(string inputBuffer);
bool checkInputDouble(string inputBuffer);
int getNumUnknowns(string inputBuffer);
void getFactorsDisplay(string inputBuffer, int numUnknowns, double matrix[][11]);
double getFactorConstant(string inputBuffer, int unknownNum);
double getFactorB(string inputBuffer);
void clearInputBuffer();
void printMatrix(double matrix[][11], int numUnknowns);
void performGaussianElimination(double matrix[][11], int numUnknowns);
void displayTransformedMatrixMessage();
void displayInitialMatrixMessage();
void performBackwardsSubstitution(double matrix[][11], double unknownVals[10], int numUnknowns);
void displayUnknownValuesMessage();
void displayUnknownValues(double unknownVals[10], int numUnknowns);

/*
Function: displayGreeting
Purpose: Greeting message intended for app launch
Return: none
Author: Jason Waid
Date Modified: 02/05/2022
*/
void displayGreeting() {

    cout << "Welcome to Assignment 1 - Program 1!\n";
    cout << "Developed by Jason Waid\n";

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

    if (!isdigit(atoi(inputBuffer.c_str())) && atoi(inputBuffer.c_str()) > 0)
        return true;

    cout << inputBuffer.c_str() << " is not valid!\n";
    clearInputBuffer();
    return false;

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

    if (!isdigit(atoi(inputBuffer.c_str())))
        return true;

    cout << inputBuffer.c_str() << " is not valid!\n";
    clearInputBuffer();
    return false;

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
        cout << "Enter number of unknowns: ";
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

    return stod(inputBuffer.c_str());

}

/*
Function: getFactorB
Purpose: Gets the value of b
Param: inputBuffer, which is the users input
Return: Double conversion of inputBuffer after validation is passed
Author: Jason Waid
Date Modified: 02/05/2022
*/
double getFactorB(string inputBuffer) {

    do {
        cout << "Enter value for b: ";
        cin >> inputBuffer;
    } while (!checkInputDouble(inputBuffer));

    return stod(inputBuffer.c_str());

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
Function: performGaussianElimination
Purpose: Performs Gaussian Elimination on the matrix
Param: double matrix[][11] which is the matrix in question, int numRows which are the number of rows, int numColumns which are the number of columns
Return: NONE
Author: Jason Waid
Date Modified: 02/06/2022
*/
void performGaussianElimination(double a[][11], int numUnknowns) {

    double m[10][11] = {};

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 11; j++) {
            m[i][j] = a[i][j];
        }
    }

    for (int k = 0; k < numUnknowns - 1; k++) {

        if (a[k][k] == 0) {
            //stop
            exit(0);
        }
        else {
            for (int i = k + 1; i < numUnknowns + 1; i++) {

                m[i][k] = a[i][k] / a[k][k];
            }
            for (int j = k; j < numUnknowns + 1; j++) {

                for (int i = k+1; i < numUnknowns; i++) {

                    cout << "Modifying Matrix[" << i << "][" << j << "]: " << a[i][j] << " to " << a[i][j] - (m[i][k] * a[k][j]) << "\n";

                    a[i][j] = a[i][j] - (m[i][k] * a[k][j]);

                    printMatrix(a, numUnknowns);
                }
            }
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
Date Modified: 02/06/2022
*/
void performBackwardsSubstitution(double matrix[][11], double unknownVals[10], int numUnknowns) {

    double temp = 0;

    for (int i = numUnknowns - 1; i >= 0; i--)
    {
        temp = 0;
        for (int j = i + 1; j < numUnknowns; j++)
            temp += matrix[i][j] * unknownVals[j];
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
    double matrix[10][10 + 1] = {};
    double unknownVals[10] = {};

    displayGreeting();


    numUnknowns = getNumUnknowns(inputBuffer);
    clearInputBuffer();

    getFactorsDisplay(inputBuffer, numUnknowns, matrix);
    displayInitialMatrixMessage();
    printMatrix(matrix, numUnknowns);

    performGaussianElimination(matrix, numUnknowns);
    displayTransformedMatrixMessage();
    printMatrix(matrix, numUnknowns);

    performBackwardsSubstitution(matrix, unknownVals, numUnknowns);
    displayUnknownValuesMessage();
    displayUnknownValues(unknownVals, numUnknowns);

}
