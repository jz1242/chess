#include "Game.h"
#include "Chess.h"
#include "Prompts.h"
int main() {
    
    ChessGame chess;
    if(chess.gameOptions() == 1){
        chess.setupBoard();
    }
    else {
        if(!chess.loadGame()){
            return 0;
        }
    }
    chess.run();

  /*  printAllPieces(&chess);
    std::cout << std::endl;
    chess.makeMove(Position(0,1), Position (0, 3));

    printAllPieces(&chess);
    std::cout << std::endl;

    chess.makeMove(Position(0,0), Position (0, 2));

    printAllPieces(&chess);
    std::cout << std::endl;
    //chess.makeMove(Position(0,1), Position (0, 3));

    chess.makeMove(Position(3, 0), Position(2, 2));
    printAllPieces(&chess);
    //std::cout <<chess.turn()<< std::endl;
    std::cout << std::endl;

    chess.makeMove(Position(3, 1), Position(3, 2));
    printAllPieces(&chess);
    std::cout << std::endl;

    chess.makeMove(Position(3, 0), Position(3, 1));
    printAllPieces(&chess);
    //std::cout <<chess.turn()<< std::endl;
    std::cout << std::endl;

    chess.makeMove(Position(3, 1), Position(1, 3));
    printAllPieces(&chess);
    //std::cout <<chess.turn()<< std::endl;
    std::cout << std::endl;

    chess.makeMove(Position(1,3), Position(2,5));
    printAllPieces(&chess);
    //std::cout <<chess.turn()<< std::endl;
    std::cout << std::endl;

    chess.makeMove(Position(1,3), Position(2,3));
    printAllPieces(&chess);
    //std::cout <<chess.turn()<< std::endl;
    std::cout << std::endl;
    chess.makeMove(Position(2,3), Position(3,2));
    printAllPieces(&chess);
    //std::cout <<chess.turn()<< std::endl;
    std::cout << std::endl;*/
}
