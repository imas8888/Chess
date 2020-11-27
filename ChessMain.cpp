/**
    Chess
    ChessMain.cpp
    Purpose: Main File

    @author Sami Khan
*/


#include"ChessBoard.h"

// Controls operation of the Program.
int main() {

  std::cout << "========================\n";
  std::cout << "Testing the Chess Engine\n";
  std::cout << "========================\n\n";

  ChessBoard cb;
  std::cout << '\n';
	
  cb.submitMove("D7", "D6");
  std::cout << '\n';

  cb.submitMove("D4", "H6");
  std::cout << '\n';
  
  cb.submitMove("D2", "D4");
  std::cout << '\n';

  cb.submitMove("F8", "B4");
  std::cout << '\n';

  std::cout << "=========================\n";
  std::cout << "Alekhine vs. Vasic (1931)\n";
  std::cout << "=========================\n\n";

  cb.resetBoard();
  std::cout << '\n';

  cb.submitMove("E2", "E4");
  cb.submitMove("E7", "E6");
  std::cout << '\n';

  cb.submitMove("D2", "D4");
  cb.submitMove("D7", "D5");
  std::cout << '\n';

  cb.submitMove("B1", "C3");
  cb.submitMove("F8", "B4");
  std::cout << '\n';

  cb.submitMove("F1", "D3");
  cb.submitMove("B4", "C3");
  std::cout << '\n';

  cb.submitMove("B2", "C3");
  cb.submitMove("H7", "H6");
  std::cout << '\n';

  cb.submitMove("C1", "A3");
  cb.submitMove("B8", "D7");
  std::cout << '\n';

  cb.submitMove("D1", "E2");
  cb.submitMove("D5", "E4");
  std::cout << '\n';

  cb.submitMove("D3", "E4");
  cb.submitMove("G8", "F6");
  std::cout << '\n';

  cb.submitMove("E4", "D3");
  cb.submitMove("B7", "B6");
  std::cout << '\n';

  cb.submitMove("E2", "E6");
  cb.submitMove("F7", "E6");
  std::cout << '\n';

  cb.submitMove("D3", "G6");
  std::cout << '\n';

  /*
  std::cout << "=========================\n";
  std::cout << "10 move checkmate\n";
  std::cout << "=========================\n\n";

  cb.resetBoard();
  cb.submitMove("E2", "E4");                                                                                                                                                                                                                  
  cb.submitMove("E7", "E5");                                                                                                                                                                                                                  
  cb.submitMove("G1", "F3");                                                                                                                                                                                                                  
  cb.submitMove("B8", "C6");                                                                                                                                                                                                                  
  cb.submitMove("B1", "C3");                                                                                                                                                                                                                  
  cb.submitMove("G8", "F6");                                                                                                                                                                                                                  
  cb.submitMove("F1", "C4");                                                                                                                                                                                                                  
  cb.submitMove("D7", "D6");                                                                                                                                                                                                                  
  cb.submitMove("F3", "G5");                                                                                                                                                                                                                  
  cb.submitMove("C8", "G4");                                                                                                                                                                                                                  
  cb.submitMove("C4", "F7");                                                                                                                                                                                                                  
  cb.submitMove("E8", "E7");                                                                                                                                                                                                                  
  cb.submitMove("C3", "D5");                                                                                                                                                                                                                  
  cb.submitMove("F6", "D5");                                                                                                                                                                                                                  
  cb.submitMove("D1", "G4");                                                                                                                                                                                                                  
  cb.submitMove("D5", "F6");                                                                                                                                                                                                                  
  cb.submitMove("G4", "E6");
  std::cout << std::endl;
  */
  std::cout << "============\n";
  std::cout << "Random Tests\n";
  std::cout << "============\n\n";
  
  cb.resetBoard();
  std::cout << std::endl;
  
  std::string firstPosition;
  std::string secondPosition;
  
  while (firstPosition != "q")
    {
      std::cout << "Moving From: ";
      std::cin >> firstPosition;
      std::cout << std::endl;

      if(firstPosition == "r")
	{
	  cb.resetBoard();
	}
      else if(firstPosition == "q")
	{
	  break;
	}
      
      std::cout << "Moving To ";
      std::cin >> secondPosition;
      std::cout << std::endl;
    
      cb.submitMove(firstPosition, secondPosition);
      std::cout << std::endl << std::endl;
    }
  
  return 0;
}
