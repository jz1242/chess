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
    int retCode = -1;
    Piece* a = getPiece(start);
    
    if(!Board::validPosition(end)) {
        Prompts::outOfBounds();
    }
    if(a->owner() != Board::playerTurn()){
        Prompts::noPiece();
    }
    else if (Board::getPiece(end) != nullptr && Board::playerTurn() == Board::getPiece(end)->owner()) {
        Prompts::blocked();
    }
    else if(!(a == nullptr)){
        if(a->validMove(start, end, *this)){
            retCode = Board::makeMove(start, end);
        }
        else{
            Prompts::illegalMove();
        }
    }
    else{
        
        Prompts::parseError();
    }

    return retCode;
}

bool checkMoveRow(Position start, Position end){
    if(start.x != end.x){
        return false;
    }
    return true;
}

bool checkMoveCol(Position start, Position end){
    if(start.y != end.y){
        return false;
    }
    return true;
}

bool checkMoveDia(Position start, Position end){
    int checkX = (int)start.x - (int)end.x;
    int checkY = (int)start.y - (int)end.y;
    if(abs(checkY) == abs(checkX)) {
        return true;
    }
    return false;
}

//Valid move functions
int Pawn::validMove(Position start, Position end,
    const Board& board) const {
    if(!(end.y == start.y + 1 && end.x == start.x)){
        return 0;
    }
    return SUCCESS;
}

int Rook::validMove(Position start, Position end,
        const Board& board) const{ 
    if(checkMoveRow(start, end)) {
        if (!board.Board::checkValidRow(start, end)) {
            return 0;
        }
    } 
    else if (checkMoveCol(start, end)) {
        if(!board.Board::checkValidCol(start, end)) {
            return 0;
        }   
    }
    else {
        return 0;
    }
    return SUCCESS;
}

int Knight::validMove(Position start, Position end,
    const Board& board) const { 
    if(!(
        (end.y == start.y + 2 && (end.x == start.x + 1 || end.x == start.x - 1)) ||
        (end.y == start.y - 2 && (end.x == start.x + 1 || end.x == start.x - 1)) ||
        (end.y == start.y + 1 && (end.x == start.x + 2 || end.x == start.x - 2)) ||
        (end.y == start.y - 1 && (end.x == start.x + 2 || end.x == start.x - 2))
        )){
        return 0;
    }
    return SUCCESS; 
}

int Bishop::validMove(Position start, Position end,
        const Board& board) const {
   if(!(checkMoveDia(start, end) && board.Board::checkValidDia(start, end))){
        return 0;
    }
    return SUCCESS; 
}

int Queen::validMove(Position start, Position end,
        const Board& board) const { 
    if(checkMoveDia(start, end)){
        if(!board.Board::checkValidDia(start, end)){
            return 0;
        }
    }
    return SUCCESS; 
}

int King::validMove(Position start, Position end,
    const Board& board) const { 
    if(!(
        !(end.y == start.y && end.x == start.x) &&
        (end.x == start.x + 1 || end.x == start.x - 1 || end.x == start.x) &&
        (end.y == start.y + 1 || end.y == start.y - 1 || end.y == start.y)
        )){
        return 0;
    }
    return SUCCESS; 
}

// Setup the chess board with its initial pieces
void ChessGame::setupBoard() {
    std::vector<int> pieces {
        ROOK_ENUM, KNIGHT_ENUM, BISHOP_ENUM, QUEEN_ENUM,
        KING_ENUM, BISHOP_ENUM, KNIGHT_ENUM, ROOK_ENUM
    };
    for (size_t i = 0; i < pieces.size(); ++i) {
        initPiece(PAWN_ENUM, WHITE, Position(i, 1));
        initPiece(pieces[i], WHITE, Position(i, 0));
        initPiece(pieces[i], BLACK, Position(i, 7));
        initPiece(PAWN_ENUM, BLACK, Position(i, 6));
    }
}

void printAllPieces(ChessGame* chess){
    //std::cout<<i<<" "<<j<<std::endl;
    for(int i = 7; i >= 0; i--){
        for(int j = 0; j <= 7; j++){
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
  
    printAllPieces(&chess);
    std::cout << std::endl;
    
    chess.makeMove(Position(2, 0), Position(4, 2));
    printAllPieces(&chess);
    std::cout << std::endl;

    chess.makeMove(Position(3, 1), Position(3, 2));
    printAllPieces(&chess);
    //std::cout <<chess.turn()<< std::endl;
    std::cout << std::endl;

    chess.makeMove(Position(2, 0), Position(4, 2));
    printAllPieces(&chess);
    //std::cout <<chess.turn()<< std::endl;
    std::cout << std::endl;

    chess.makeMove(Position(4,2), Position(2,4));
    printAllPieces(&chess);
    //std::cout <<chess.turn()<< std::endl;
    std::cout << std::endl;

    chess.makeMove(Position(2,4), Position(3,3));
    printAllPieces(&chess);
    //std::cout <<chess.turn()<< std::endl;
    std::cout << std::endl;
}
