# Chess

Chess Game coded in an OOP fashion. With only CLI currently.

### Installation
1. Download and unzip this respository
2. Use GNU Make to create an executable using the following command in this directory `make -f makefile`
3. Run the executable named: *chess* (or *chess.exe* depending on OS)

### How to Use
* The program initially prints a game just to show that the code works
* It will then start a new game
* When asked *Moving From:* and *Moving To:*, please input positions such as **F2** where the character ranges from *A* to *H* and the digit ranges from *1* to *8*
* All the usual rules of chess apply
* The program will notify you what move has been made or if an error has occured
* Notifications include:
    * A mistake has been made when trying to move pieces
    * A player is in check
    * A player is in checkmate and the game is over
