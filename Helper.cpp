/**
    Chess
    Helper.cpp
    Purpose: Implementation File for helper functions

    @author Sami Khan
    @version 1.7 10/12/16 
*/

#include "Helper.h"

//Checks if a list of vectors contains a given vector.
bool contains(std::vector<std::vector<int>> inputList, std::vector<int> inputVector)
{
  return find(inputList.begin(),inputList.end(),inputVector) != inputList.end();
}

//Simplifies a vector.
std::vector<int> simplify(std::vector<int> inputVector)
{
  std::vector<int> outputVector;
  int commonDivisor = std::max(abs(inputVector[0]), abs(inputVector[1]));
  
  for(int i = 0; i < 2; i++)
    {
      double simp = (double)inputVector[i]/(double)commonDivisor, temp;
      
      if(modf(simp, &temp) != 0) //If division returns fractional part
	{
	  outputVector = {0,0};
	  
	  break;
	}
      
      outputVector.push_back((int)simp);
    }
  
  return outputVector;
}

//Check two position vectors lie on the chess board.
bool checkEntries(std::vector<int> moveFrom, std::vector<int> moveTo)
{
  for(int i = 0; i < 2; i++)
    {
      if(moveFrom[i] < 1 || moveFrom[i] > 8 || moveTo[i] < 1 || moveTo[i] > 8)
	{
	  return false;
	}
    }
  
  return true;
}

//Converts a string of two characters into a vector.
std::vector<int> toVector(const std::string POSITION)
{
  std::vector<int> outputVector;
  outputVector.push_back(((int)POSITION[0]) - ASCII_LETTER);
  outputVector.push_back(((int)POSITION[1]) - ASCII_NUMBER);
  
  return outputVector;
}

//Overloading "+" operator for vectors.
std::vector<int> operator+(const std::vector<int>& LHS, const std::vector<int>& RHS)
{
  std::vector<int> result;

  for(int i = 0; i < 2; i++)
    {
      result.push_back(LHS[i] + RHS[i]);
    }
  
  return result;
}

//Overloading "-" operator for vectors.
std::vector<int> operator-(const std::vector<int>& LHS, const std::vector<int>& RHS)
{
  std::vector<int> result;

  for(int i = 0; i < 2; i++)
    {
      result.push_back(LHS[i] - RHS[i]);
    }
  
  return result;
}

//Overloading "!=" operator for vectors.
bool operator!=(const std::vector<int>& LHS, const std::vector<int>& RHS)
{
  if((LHS[0] == RHS[0]) && (LHS[1] == RHS[1]))
    {
      return false;
    }
  
  return true;
}
