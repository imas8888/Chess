/**
    Chess
    Pieces.cpp
    Purpose: Implementation file for all the pieces

    @author Sami Khan
    @version 1.13 10/12/19 
*/

#include "Pieces.h"

//Constructor for singular (only one for each colour) pieces.
Piece::Piece(bool colourPar)
{
  colour = colourPar;
  alignment = 'u';
  numberOfMoves = 0;
}

//Constructor for dual (two for each colour) pieces.
Piece::Piece(bool colourPar, char alignmentPar)
{
  colour = colourPar;
  alignment = alignmentPar;
  numberOfMoves = 0;
}

//Returns the current position of the piece.
std::vector<int> Piece::getPosition()
{
  return currentPosition;
}

//Returns the type of a piece.
std::string Piece::getType()
{
  return type;
}

//Returns the colour of a piece.
bool Piece::getColour()
{
  return colour;
}

// Function that returns if a piece can move to a given location on the board.
bool Piece::canMoveTo(std::map<std::vector<int>, Piece*> pieceAt, std::vector<int> destinationSquare)
{
  std::vector<int> vectorNeededToMove = destinationSquare - currentPosition;
  std::vector<int> vectorStep = simplify(vectorNeededToMove);
  std::vector<int> testPosition = currentPosition;
  
  int divisor = std::max(abs(vectorNeededToMove[0]), abs(vectorNeededToMove[1]));
  
  if(!contains(possibleVectors,vectorStep)) //Checking if the piece can move as requested.
    {
      return false;
    }
  if((pieceAt[destinationSquare] != NULL) && (pieceAt[destinationSquare] -> getColour() == colour)) //Checking that a piece is not moving into a friendly piece.
    {
      return false;
    }
  
  for(int i = 0; i < divisor - 1; i++) //Checking all cells in the path for any blocking pieces.
    {
      testPosition = testPosition + vectorStep;
      
      if(pieceAt[testPosition] != NULL)
	{
	  return false;
	}
    }
  
  return true;
}

//Function to see if the piece is in check.
bool Piece::isCheck(std::map<std::vector<int>, Piece*> pieceAt)
{
  return false;
}

//Function to see if the piece is in checkmate.
bool Piece::isCheckMate(std::map<std::vector<int>, Piece*> pieceAt)
{
  return false;
}

//Function that changes the current position of a piece to the given position and increases moves by 1.
void Piece::makeMove(std::vector<int> destinationSquare)
{
  currentPosition = destinationSquare;
  numberOfMoves++;
}

//Function that changes the current position of a piece to the given position and decreases moves by 1.
void Piece::undoMove(std::vector<int> originalSquare)
{
  currentPosition = originalSquare;
  numberOfMoves--;
}

//Constructor for King pieces.
King::King(bool colourPar):Piece(colourPar)
{
  type = (char*)"King";
  possibleVectors = {{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1}};
  
  if(colour == 0)//White
    {
      initialPosition.push_back(5);
      initialPosition.push_back(1);
    }
  else
    {
      initialPosition.push_back(5);
      initialPosition.push_back(8);
    }
  
  currentPosition = initialPosition;
}

//Function that returns if a king can move to a given location on the board.
bool King::canMoveTo(std::map<std::vector<int>, Piece*> pieceAt, std::vector<int> destinationSquare)
{
  std::vector<int> vectorStep = destinationSquare - currentPosition; //No need to simplify here as king can only move 1 block
  std::vector<int> testPosition = currentPosition;
  
  if(!contains(possibleVectors,vectorStep))
    {
      return false;
    }
  if((pieceAt[destinationSquare] != NULL) && (pieceAt[destinationSquare] -> getColour() == colour))
    {
      return false;
    }
  
  std::map<std::vector<int>, Piece*> pieceAtLocal = pieceAt;
  
  pieceAtLocal[currentPosition] = nullptr; //Making the move and checking if the king ends up in check.
  pieceAtLocal[destinationSquare] = this;
  
  std::vector<int> previousPosition = currentPosition;
  
  makeMove(destinationSquare);
  
  if(isCheck(pieceAtLocal))
    {
      undoMove(previousPosition);
      return false;
    }
  
  undoMove(previousPosition);
  
  return true;
}

//Function to see if the king is in check.
bool King::isCheck(std::map<std::vector<int>, Piece*> pieceAt)
{
  std::vector<std::vector<int>> listOfCurrentPositions = listOfKeys(pieceAt); //List of locations of all pieces.
  
  for(int i = 0; (unsigned)i < listOfCurrentPositions.size(); i++)
    {
      std::vector<int> testPosition = listOfCurrentPositions[i];
      auto testPiece = pieceAt[testPosition];
      bool testColour = testPiece -> getColour();
      
      if(testColour == colour) //Filtering out friendly pieces.
	{
	  continue;
	}
      if(testPiece -> canMoveTo(pieceAt, currentPosition)) //If any piece can move to the kings position then the king is in check.
	{
	  return true;
	}
    }
  
  return false;
}

//Function to see if the king is in checkmate.
bool King::isCheckMate(std::map<std::vector<int>, Piece*> pieceAt)
{
  if(!isCheck(pieceAt)) //If the king is not in check then no need to check anything else.
    {
      return false;
    }

  Piece* attacker;
  std::vector<std::vector<int>> listOfCurrentPositions = listOfKeys(pieceAt);
  std::vector<std::vector<int>> routeOfAttacker;
  
  for(int i = 0; (unsigned)i < listOfCurrentPositions.size(); i++) //Finding the attacking piece
    {
      std::vector<int> testPosition = listOfCurrentPositions[i];
      auto testPiece = pieceAt[testPosition];
      bool testColour = testPiece -> getColour();
      
      if(testColour == colour)
	{
	  continue;
	}
      if(testPiece -> canMoveTo(pieceAt, currentPosition))
	{
	  attacker = testPiece;
	  break;
	}
    }

  std::vector<int> attackerPosition = attacker -> getPosition(); //Getting information of the attacker.
  std::vector<int> vectorOfAttack = currentPosition - attackerPosition;
  int length = 1;
  
  if(attacker -> getType() != "Knight")
    {
      length = std::max(abs(vectorOfAttack[0]),abs(vectorOfAttack[1]));
      vectorOfAttack = simplify(vectorOfAttack);
    }
  
  for(int i = 0; i < length; i++) //Making a list of all the blocks that the attacking piece passes through so the king can be defended by moving friendly piece in this path.
    {
      routeOfAttacker.push_back(attackerPosition);
      attackerPosition = attackerPosition + vectorOfAttack;
    }
  
  std::vector<std::vector<int>> kingPossiblePositions;
  
  for(int i = 0; i < 8; i++) //Creating a list of the possible positions that the king can move to.
    {
      std::vector<int> futurePosition = currentPosition + possibleVectors[i];
      
      if(futurePosition[0] > 0 && futurePosition[0] < 9 && futurePosition[1] > 0 && futurePosition[1] < 9)
	{
	  kingPossiblePositions.push_back(futurePosition);
	}
    }

  for(int i = 0; i < 8; i++)
    {
      if(canMoveTo(pieceAt, kingPossiblePositions[i])) //Check to see if the king can move anywhere else...
	{
	  std::vector<int> previousPosition = currentPosition;
	  makeMove(kingPossiblePositions[i]);
	  std::map<std::vector<int>, Piece*> pieceAtLocal = pieceAt; //Making a dummy move.
	  pieceAtLocal[previousPosition] = nullptr;
	  pieceAtLocal[currentPosition] = this;
	  
	  if(!isCheck(pieceAtLocal)) //...without being in check again.
	    {
	      undoMove(previousPosition);
	      return false;
	    }
	  
	  undoMove(previousPosition);
	}
    }

  for(int i = 0; (unsigned)i < listOfCurrentPositions.size(); i++) //Attempting to move all friendly pieces in the route of the attacker.
    {
      std::vector<int> testPosition = listOfCurrentPositions[i];
      auto testPiece = pieceAt[testPosition];
      bool testColour = testPiece -> getColour();
      
      if(testColour != colour) //Filetring out all enemy pieces.
	{
	  continue;
	}
      
      for(int j = 0; (unsigned)j < routeOfAttacker.size(); j++)
	{
	  if(testPiece -> canMoveTo(pieceAt, routeOfAttacker[j]))
	    {
	      return false;
	    }
	}
    }
  
  return true;
}

//Function which lists all the keys in a map.
std::vector<std::vector<int>> King::listOfKeys(std::map<std::vector<int>, Piece*> pieceAt)
{
  std::vector<std::vector<int>> outputList;
  std::pair<std::vector<int>, Piece*> check;
  
  BOOST_FOREACH(check, pieceAt)
    {
      if(check.second != NULL)
	{
	  outputList.push_back(check.first);
	}
    }
  
  return outputList;
}

//Constructor for Rook pieces.
Rook::Rook(int colourPar, char alignmentPar):Piece(colourPar, alignmentPar)
{
  type = (char*)"Rook";
  possibleVectors = {{1,0},{0,1},{-1,0},{0,-1}};
  
  if(colour == 0)
    {
      if(alignment == 'l')
	{
	  initialPosition.push_back(1);
	}
      else
	{
	  initialPosition.push_back(8);
	}
      
      initialPosition.push_back(1);
    }
  else
    {
      if(alignment == 'l')
	{
	  initialPosition.push_back(1);
	}
      else
	{
	  initialPosition.push_back(8);
	}
      
      initialPosition.push_back(8);
    }
  
  currentPosition = initialPosition;
}

//Constructor for the Bishop pieces.
Bishop::Bishop(int colourPar, char alignmentPar):Piece(colourPar, alignmentPar)
{
  type = (char*)"Bishop";
  possibleVectors = {{1,1},{-1,1},{-1,-1},{1,-1}};
  
  if(colour == 0)
    {
      if(alignment == 'l')
	{
	  initialPosition.push_back(3);
	}
      else
	{
	  initialPosition.push_back(6);
	}
      
      initialPosition.push_back(1);
    }
  else
    {
      if(alignment == 'l')
	{
	  initialPosition.push_back(3);
	}
      else
	{
	  initialPosition.push_back(6);
	}
      
      initialPosition.push_back(8);
    }
  
  currentPosition = initialPosition;
}

//Constructor for Queen pieces.
Queen::Queen(int colourPar):Piece(colourPar)
{
  type = (char*)"Queen";
  possibleVectors = {{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1}};
  
  if(colour == 0)
    {
      initialPosition.push_back(4);
      initialPosition.push_back(1);
    }
  else
    {
      initialPosition.push_back(4);
      initialPosition.push_back(8);
    }
  
  currentPosition = initialPosition;
}

//Constructor for Knight pieces.
Knight::Knight(int colourPar, char alignmentPar):Piece(colourPar, alignmentPar)
{
  type = (char*)"Knight";
  possibleVectors = {{2,1},{1,2},{-1,2},{-2,1},{-2,-1},{-1,-2},{1,-2},{2,-1}};
  
  if(colour == 0)
    {
      if(alignment == 'l')
	{
	  initialPosition.push_back(2);
	}
      else
	{
	  initialPosition.push_back(7);
	}
      
      initialPosition.push_back(1);
    }
  else
    {
      if(alignment == 'l')
	{
	  initialPosition.push_back(2);
	}
      else
	{
	  initialPosition.push_back(7);
	}
      
      initialPosition.push_back(8);
    }
  
  currentPosition = initialPosition; 
}

//Function that returns if a knight can move to a given location on the board.
bool Knight::canMoveTo(std::map<std::vector<int>, Piece*> pieceAt, std::vector<int> destinationSquare)
{
  std::vector<int> vectorStep = destinationSquare - currentPosition;
  std::vector<int> testPosition = currentPosition;
  //No need to check for any pieces in the way.
  if(!contains(possibleVectors,vectorStep))
    {
      return false;
    }
  if((pieceAt[destinationSquare] != NULL) && (pieceAt[destinationSquare] -> getColour() == colour))
    {
      return false;
    }
  
  return true;
}

//Constructor for Pawn pieces.
Pawn::Pawn(int colourPar, int pawnNumberPar):Piece(colourPar)
{
  type = (char*)"Pawn";
  pawnNumber = pawnNumberPar;

  if(colour == 0)
    {
      possibleVectors = POSSIBLE_VECTORS_WHITE;
      initialPosition = {pawnNumber, 2};
    }
  else
    {
      possibleVectors = POSSIBLE_VECTORS_BLACK;
      initialPosition = {pawnNumber, 7};
    }
  
  currentPosition = initialPosition;
}

//Function that returns if a pawn can move to a given location on the board.
bool Pawn::canMoveTo(std::map<std::vector<int>, Piece*> pieceAt, std::vector<int> destinationSquare)
{
  std::vector<int> vectorStep = destinationSquare - currentPosition;
  std::vector<int> testPosition = currentPosition;
  std::vector<std::vector<int>> currentPossibleVectors = possibleVectors;
  
  if(pieceAt[currentPosition + possibleVectors[1]] != NULL && (destinationSquare == currentPosition + possibleVectors[1] || destinationSquare == currentPosition + possibleVectors[0])) //If there is a piece right infront of the pawn.
    {
      return false;
    }
  if(pieceAt[currentPosition + possibleVectors[0]] != NULL && destinationSquare == currentPosition + possibleVectors[0]) //If there is a piece in the way of the two forward move.
    {
      return false;
    }

  //Possible vectors are of the form {first 2 cell move, single forward move, right take move, left take move}.
  //The code below just chooses the right vectors to be used in the given situation.
  if(numberOfMoves != 0) //If the pawn is on its first move.
    {
      if(pieceAt[destinationSquare] == NULL) //If there is no piece at the destination block.
	{
	  currentPossibleVectors = std::vector<std::vector<int>>(possibleVectors.begin()+1, possibleVectors.begin()+2);
	}
      else
	{
	  currentPossibleVectors = std::vector<std::vector<int>>(possibleVectors.begin()+1, possibleVectors.end());
	}
    }
  else
    {
      if(pieceAt[destinationSquare] == NULL)
	{
	  currentPossibleVectors = std::vector<std::vector<int>>(possibleVectors.begin(), possibleVectors.begin()+2);
	}
    }
  
  if(!contains(currentPossibleVectors,vectorStep))
    {
      return false;
    }
  if((pieceAt[destinationSquare] != NULL) && (pieceAt[destinationSquare] -> getColour() == colour)) //If the pawn is trying to take a friendly piece.
    {
      return false;
    }
  
  return true;
}
