/**
    Chess
    Helper.h
    Purpose: Header File for helper functions

    @author Sami Khan
    @version 1.6 10/12/16 
*/

#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <string>
#include <boost/foreach.hpp>
#include <math.h>

const int ASCII_LETTER = 64; //Used when converting chraracter to integer
const int ASCII_NUMBER = 48;

/**
    Checks if a list of vectors contains a given vector.

    @param inputList - List of vectors which will be checked against.
    @param inputVector - The vector which will be checked against the inputList.
    @return True if the vector is in the list, otherwise false.
*/
bool contains(std::vector<std::vector<int>> inputList, std::vector<int> inputVector);

/**
    Simplifies a vector.

    @param inputVector - The vector to be simplified.
    @return The simplified vector or a zero vector if simplification returns non-interger values.
*/
std::vector<int> simplify(std::vector<int> inputVector);

/**
    Check two position vectors lie on the chess board.
    @param moveFrom - The first position vector to be checked.
    @param moveTo - The second position vector to be checked.
    @return True if all entries are within the range 1-8 otherwise false.
*/
bool checkEntries(std::vector<int> moveFrom, std::vector<int> moveTo);

/**
    Converts a string of two characters into a vector.
    @param POSITION - The string input given to function e.g. "A3".
    @return A vector created using the conversion A->1, B->2,...,H->8.
*/
std::vector<int> toVector(const std::string POSITION);

/**
    Overloading "+" operator for vectors.
    @param LHS - The vector on the left hand side of the addition.
    @param RHS - The vector on the right hands side of the addition.
    @return The vector which is the result of adding LHS and RHS.
*/
std::vector<int> operator+(const std::vector<int>& LHS, const std::vector<int>& RHS);

/**
    Overloading "-" operator for vectors.
    @param LHS - The vector on the left hand side of the subtraction.
    @param RHS - The vector on the right hands side of the subtraction.
    @return The vector which is the result of subtracting RHS from LHS.
*/
std::vector<int> operator-(const std::vector<int>& LHS, const std::vector<int>& RHS);

/**
    Overloading "!=" operator for vectors.
    @param LHS - The vector on the left hand side of the comparison.
    @param RHS - The vector on the right hands side of the comparison.
    @return True if LHS is not equal to RHS otherwise false.
*/
bool operator!=(const std::vector<int>& LHS, const std::vector<int>& RHS);

#endif
