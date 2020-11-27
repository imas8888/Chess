/**
    Chess
    ChessBoard.h
    Purpose: Header file for ChessBoard class

    @author Sami Khan
    @version 1.5 10/12/19
*/

#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "Helper.h"
#include "Pieces.h"

class ChessBoard
{
  std::map<bool, std::string> colourMap;
  std::map<std::vector<int>, Piece*> pieceAt;
  
  bool currentColour;
  
 public:

  /**
      Constructor for a chessboard.
  */
  ChessBoard();

  /**
      Returns the colour of the piece.

      @return True if colour is white otherwise false.
  */
  bool getCurrentColour();

  /**
      Function to check if a certain cell on the board is empty.

      @param cellToCheck - Vector position of cell that needs to be checked.
      @return True if cell is empty otherwise false.
  */
  bool isEmpty(std::vector<int> cellToCheck);

  /**
      Function to find the location of the king of a given colour.

      @param colour - The colour of the king to find.
      @return Vector that represents the location of the king
  */
  std::vector<int> locateKing(bool colour);

  /**
      Function that initialises the pieces on the board.
  */
  void setBoard();

  /**
      Function which passes a move into the program.

      @param sourceSquare - The string position of where the piece is moving from.
      @param destinationSquare - The string position of where the piece is moving.
  */
  void submitMove(std::string sourceSquare, std::string destinationSquare);

  /**
      Function to reset the board (reset the pieces)
  */
  void resetBoard();
};

#endif
