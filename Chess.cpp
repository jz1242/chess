#undef FOR_RELEASE

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Game.h"
#include "Chess.h"
#include "Prompts.h"

// Make a move on the board. Return an int, with < 0 being failure
int ChessGame::makeMove(Position start, Position end) {
    // Possibly implement chess-specific move logic here
    //
    // We call Board's makeMove to handle any general move logic
    // Feel free to use this or change it as you see fit
    int retCode = Board::makeMove(start, end);
    return retCode;
}

// Setup the chess board with its initial pieces
void ChessGame::setupBoard() {
    std::vector<int> pieces {
        ROOK_ENUM, KNIGHT_ENUM, BISHOP_ENUM, QUEEN_ENUM,
        KING_ENUM, BISHOP_ENUM, KNIGHT_ENUM, ROOK_ENUM
    };
    for (size_t i = 0; i < pieces.size(); ++i) {
        initPiece(PAWN_ENUM, WHITE, Position(1, i));
        initPiece(pieces[i], WHITE, Position(0, i));
        initPiece(pieces[i], BLACK, Position(7, i));
        initPiece(PAWN_ENUM, BLACK, Position(6, i));
    }
}

void printAllPieces(ChessGame* chess){
    //std::cout<<i<<" "<<j<<std::endl;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            Piece* a = chess->getPiece(Position(i, j));
            if(!(a == nullptr)){
                std::cout<<a->id()<<" ";
            }
            else{
                std::cout<<"e ";
            }

        }
        std::cout<<std::endl;
    }
}

int main() {
    ChessGame chess;
    //chess.run();
    chess.setupBoard();
  /*  std::vector<int> q;
    q[0] = 0;
    q[1] = 0;
        printf("%u", q[0]);*/
    printAllPieces(&chess);

}
