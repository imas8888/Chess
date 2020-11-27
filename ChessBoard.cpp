/**
    Chess
    ChessBoard.cpp
    Purpose: Implementation file for ChessBoard class

    @aurthor Sami Khan
    @version 1.12 10/12/19
*/

#include "ChessBoard.h"

//Constructor for a chessboard.
ChessBoard::ChessBoard()
{
  colourMap[0] = "White";
  colourMap[1] = "Black";

  setBoard();
}

//Returns the colour of the piece.
bool ChessBoard::getCurrentColour()
{
  return currentColour;
}

//Function to check if a certain cell on the board is empty.
bool ChessBoard::isEmpty(std::vector<int> cellToCheck)
{
  if(pieceAt[cellToCheck] == NULL)
    {
      return true;
    }
  
  return false;
}

//Function to find the location of the king of a given colour.
std::vector<int> ChessBoard::locateKing(bool colour)
{
  std::pair<std::vector<int>, Piece*> check;
  
  BOOST_FOREACH(check, pieceAt)
    {
      if(check.second != NULL)
	{
	  auto piece =  check.second;
	  
	  if((piece -> getType() == "King") && (piece -> getColour() == colour))
	    {
	      return check.first; //The first part of each pair is the position.
	    }
	}
    }
  
  return {0,0};
}

//Function that initialises the pieces on the board.
void ChessBoard::setBoard()
{
  currentColour = 0; //Start with white

  for(int i = 0; i < 2; i++)
    {
      pieceAt[King(i).getPosition()] = new King(i);
      pieceAt[Rook(i, 'l').getPosition()] = new Rook(i, 'l');
      pieceAt[Rook(i, 'r').getPosition()] = new Rook(i, 'r');
      pieceAt[Bishop(i, 'l').getPosition()] = new Bishop(i, 'l');
      pieceAt[Bishop(i, 'r').getPosition()] = new Bishop(i, 'r');
      pieceAt[Queen(i).getPosition()] = new Queen(i);
      pieceAt[Knight(i, 'l').getPosition()] = new Knight(i, 'l');
      pieceAt[Knight(i, 'r').getPosition()] = new Knight(i, 'r');
      
      for(int j = 1; j < 9; j++)
	{
	  pieceAt[Pawn(i,j).getPosition()] = new Pawn(i,j);
	}
    }
  
  std::cout << "A new chess game is started!\n";
}

//Function which passes a move into the program.
void ChessBoard::submitMove(std::string sourceSquare, std::string destinationSquare)
{
  if(pieceAt[locateKing(currentColour)] -> isCheckMate(pieceAt)) //If the game is already in checkmate.
    {
      std::cout << "The game is already finished!\n";
      
      return;
    }
  
  std::vector<int> moveFrom = toVector(sourceSquare);
  std::vector<int> moveTo = toVector(destinationSquare);
  
  if(!checkEntries(moveFrom, moveTo))
    {
      std::cout << "One of the entries did not lie on the Chess Board or the entry was in an invalid format!\n";
      
      return;
    }
  if(isEmpty(moveFrom))
    {
      std::cout << "There is no piece at position " << sourceSquare << "!\n";
      
      return;
    }
  
  auto piece = pieceAt[moveFrom]; //Gathering information about piece that needs to be moved.
  bool colourBool = piece -> getColour();
  std::string typeOfPiece = piece -> getType();
  std::string colour = colourMap[colourBool];
  std::string outputText;

  if(colourBool != currentColour)
    {
      std::cout << "It is not " << colour << "'s turn to move!\n";
      
      return;
    }
  if(!(piece -> canMoveTo(pieceAt, moveTo)))
    {
      std::cout << colour << "'s " << typeOfPiece << " cannot move to " << destinationSquare << "!\n";
      
      return;
    }
 
  Piece* deadPiece = nullptr;
  std::string deadColour;
  std::string deadType;
  
  if(pieceAt[moveTo] != nullptr) //Checking if a piece is getting captured
    {
      deadPiece = pieceAt[moveTo];
      deadColour = colourMap[deadPiece -> getColour()];
      deadType = deadPiece -> getType();
    }

  currentColour = !currentColour; //Chaning the current colour: i.e. changing player.
  pieceAt[moveFrom] = nullptr; //Making the move.
  pieceAt[moveTo] = piece;
  piece -> makeMove(moveTo);

  //Preparing possible output.
  outputText = colour + "'s " + typeOfPiece + " moves from " + sourceSquare + " to " + destinationSquare;

  if(deadPiece != nullptr)
    {
      outputText = outputText + " taking " + deadColour + "'s " + deadType;
    }
  
  outputText = outputText + "\n";

  if(pieceAt[locateKing(!currentColour)] -> isCheck(pieceAt)) //If the king is in check...
    {
      pieceAt[moveFrom] = piece; //Undo the move.
      pieceAt[moveTo] = nullptr;
      
      if(deadPiece != NULL)
	{
	  pieceAt[moveTo] = deadPiece;
	}
      
      piece -> undoMove(moveFrom);
      currentColour = !currentColour; //Revert player change.
      std::cout <<  colour << "'s " << typeOfPiece << " cannot move to " << destinationSquare << " as the King is in Check!\n"; //Give error output.
      
      return; //Exit this move.
    }
  
  std::cout << outputText;
  
  if(pieceAt[locateKing(currentColour)] -> isCheck(pieceAt)) //Checking if opposing king has been put in check...
    {
      std::cout << colourMap[currentColour] << " is in check";
      
      if(King(currentColour).isCheckMate(pieceAt)) //mate
	{
	  std::cout << "mate";
	}
      
      std::cout << std::endl;
    }

  return;
}

//Function to reset the board (reset the pieces)
void ChessBoard::resetBoard()
{
  pieceAt.clear(); //Clear the map
  setBoard(); //(Re)set the board again
}
