/**
    Chess
    Pieces.h
    Purpose: Header file for all the pieces

    @author Sami Khan
    @version 1.6 10/12/19 
*/

#ifndef PIECES_H
#define PIECES_H

#include "Helper.h"

class Piece
{
 protected:
  std::vector<int> initialPosition, currentPosition;
  std::vector<std::vector<int>> possibleVectors;
  
  std::string type;
  bool colour; // White = 0, Black = 1
  char alignment; // l - left, r - right, u - undefined (of King) (Viewed from White side)
  int numberOfMoves;

 public:

  /**
      Constructor for singular (only one for each colour) pieces.

      @param colourPar - Relates to the colour that the piece belongs to.
  */
  Piece(bool colourPar);

  /**
      Constructor for dual (two for each colour) pieces.

      @param colourPar - Relates to the colour that the piece belongs to.
      @param alignmentPar - Alignment (defined above) of the piece.
  */
  Piece(bool colourPar, char alignmentPar);

  /**
      Returns the current position of a piece.
      
      @return Position vector of the piece.
  */
  virtual std::vector<int> getPosition();

  /**
      Returns the type of a piece.

      @return String which is the type of the piece.
  */
  virtual std::string getType();

  /**
      Returns the colour of a piece.

      @return Bool relating to the colour of the piece.
  */
  virtual bool getColour();

  /**
     Function that returns if a piece can move to a given location on the board.

     @param pieceAt - The map of pieces to their locations.
     @param destinationSquare - The position to which the piece is being moved to.
     @return True if the piece can be moved to the destinationSquare, false otherwise.
  */
  virtual bool canMoveTo(std::map<std::vector<int>, Piece*> pieceAt, std::vector<int> destinationSquare);

  /**
      Function to see if the piece is in check.
      This is only for King piece and is described there.
  */
  virtual bool isCheck(std::map<std::vector<int>, Piece*> pieceAt);

  /** 
      Function to see if the piece is in checkmate.
      This is only for the King piece and is described there.
  */
  virtual bool isCheckMate(std::map<std::vector<int>, Piece*> pieceAt);

  /**
      Function that changes the current position of a piece to the given position and increases moves by 1.
      
      @param destinationSquare - The position vector that the piece is required to be moved to.
  */
  void makeMove(std::vector<int> destinationSquare);

  /**
      Function that changes the current position of a piece to the given position and decreases moves by 1.

      @param originalSquare - The position vector that the piece is required to be moved back to.
  */
  void undoMove(std::vector<int> originalSquare);
};

struct King:public Piece
{
  
  /**
      Constructor for King pieces.

      @param colourPar - Relates to the colour that the king belongs to.
  */
  King(bool colourPar);

  /**
     Function that returns if a king can move to a given location on the board.
     This is different to the other pieces
  */
  bool canMoveTo(std::map<std::vector<int>, Piece*> pieceAt, std::vector<int> destinationSquare) override;

  /**
      Function to see if the king is in check.

      @param pieceAt - The map connecting the pieces to their location.
      @return True if the King is in check, otherwise false.
  */
  bool isCheck(std::map<std::vector<int>, Piece*> pieceAt) override;

  /**
      Function to see if the king is in checkmate.

      @param pieceAt - The map connecting the pieces to their location.
      @return True if the King is in checkmate, otherwise false.
  */
  bool isCheckMate(std::map<std::vector<int>, Piece*> peiceAt) override;

  /**
      Function which lists all the keys in a map.
      
      @param pieceAt - The map connecting the pieces to their location.
      @return List of positions of all currently active pieces.
  */
  std::vector<std::vector<int>> listOfKeys(std::map<std::vector<int>, Piece*> pieceAt);
};

struct Rook:public Piece
{
  
  /**
      Constructor for Rook pieces.

      @param colourPar - Relates to the colour that the rook belongs to.
      @param alignmentPar - Alignment (defined above) of the rook.
  */
  Rook(int colourPar, char alignmentPar);
};

struct Bishop:public Piece
{
  
  /**
      Constructor for Bishop pieces.

      @param colourPar - Relates to the colour that the bishop belongs to.
      @param alignmentPar - Alignment (defined above in) of the bishop.
  */
  Bishop(int colourPar, char alignmentPar);
};

struct Queen:public Piece
{
  
  /**
      Constructor for Queen pieces.

      @param colourPar - Relates to the colour that the queen belongs to.
  */
  Queen(int colourPar);
};

struct Knight:public Piece
{
  
  /**
      Constructor for Knight pieces.

      @param colourPar - Relates to the colour that the knight belongs to.
      @param alignmentPar - Alignment (defined above) of the knight.
  */
  Knight(int colourPar, char alignmentPar);

  /**
     Function that returns if a knight can move to a given location on the board.
     This is different to the other pieces
  */
  bool canMoveTo(std::map<std::vector<int>, Piece*> pieceAt, std::vector<int> destinationSquare) override;
};

class Pawn:public Piece
{
  std::vector<std::vector<int>> const POSSIBLE_VECTORS_WHITE = {{0,2},{0,1},{1,1},{-1,1}};
  std::vector<std::vector<int>> const POSSIBLE_VECTORS_BLACK = {{0,-2},{0,-1},{1,-1},{-1,-1}};
  int pawnNumber; // 1-9 starting from left (viewed from white side)
 public:
  
  /**
      Constructor for Pawn pieces.

      @param colourPar - Relates to the colour that the pawn belongs to.
      @param pawnNumberPar - Alignment (defined above) of the pawn.
  */
  Pawn(int colourPar, int pawnNumberPar);

  /**
     Function that returns if a pawn can move to a given location on the board.
     This is different to the other pieces
  */
  bool canMoveTo(std::map<std::vector<int>, Piece*> pieceAt, std::vector<int> destinationSquare) override;
};

#endif
