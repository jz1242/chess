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
    int retCode = 0;
    Piece* a = getPiece(start);
    Piece* temp = Board::getPiece(end);
    if(!Board::validPosition(end)) {
        retCode = -7;
    }
    else if(a != nullptr){
        if(a->owner() != Board::playerTurn()){
            retCode = -6;
        }
        else if (Board::getPiece(end) != nullptr && Board::playerTurn() == Board::getPiece(end)->owner()) {
            retCode = -5;
        }
        else if(a->validMove(start, end, *this)){
            if(Board::getPiece(end) != nullptr){
                retCode = 3;
            }
            if(a->id() == 0){
                Board::promote(end);
            }

            if(inCheck() == 1 && playerTurn() == WHITE){
                Board::makeMove(start, end);
                if(inCheck() == 1){
                    Board::makeMove(end, start);
                    m_pieces[index(end)] = temp;
                    retCode = -3;
                }
            }
            else if(inCheck() == 2 && playerTurn() == BLACK){
                Board::makeMove(start, end);
                if(inCheck() == 2){
                    Board::makeMove(end, start);
                    m_pieces[index(end)] = temp;
                    retCode = -3;
                }
            }
            else if(inCheck() == -1){
                Board::makeMove(start, end);
                if(inCheck() == 2 && playerTurn() == BLACK){
                    Board::makeMove(end, start);
                    m_pieces[index(end)] = temp;
                    retCode = -2;
                }
                else if(inCheck() == 1 && playerTurn() == WHITE){
                    Board::makeMove(end, start);
                    m_pieces[index(end)] = temp;
                    retCode = -2;
                }
            }
            else{
                Board::makeMove(start, end);
            }
        }
        else{
            retCode = -1;
        }

    }
    else{
        retCode = -6;
    }
    return retCode;
}

bool Board::checkMoveRow(Position start, Position end) const{
    if(start.y == end.y){
        if(start.x == end.x){
            return false;
        }
        return true;
    }
    return false;
}

bool Board::checkMoveCol(Position start, Position end) const{
    if(start.x == end.x){
        if(start.y == end.y){
            return false;
        }
        return true;
    }
    return false;
}

bool Board::checkMoveDia(Position start, Position end) const{
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
    if(board.Board::getPiece(start)->owner() == WHITE){
        if(end.x == start.x && end.y == start.y + 2 && start.y == 1){
            if(board.Board::getPiece(end) != nullptr){
                return 0;
            }
            if(!(board.Board::checkValidCol(start, end))){
                return 0;
            }
        }
        else if(end.x == start.x && end.y == start.y + 1){
            if(board.Board::getPiece(end) != nullptr){
                    return 0;
            }
            if(!(board.Board::checkValidCol(start, end))){
                return 0;
            }
        }
        else if(end.x == start.x + 1 && end.y == start.y + 1){
            if(board.Board::getPiece(end) == nullptr){
                return 0;
            }
        }
        else if(end.x == start.x - 1 && end.y == start.y + 1){
            if(board.Board::getPiece(end) == nullptr){
                return 0;
            }
        }
        else{
            return 0;
        }
    }
    else{
        if(end.x == start.x && end.y == start.y - 2 && start.y == 6){
                if(board.Board::getPiece(end) != nullptr){
                    return 0;
                }
                if(!(board.Board::checkValidCol(start, end))){
                    return 0;
                }
            }
            else if(end.x == start.x && end.y == start.y - 1){
                if(board.Board::getPiece(end) != nullptr){
                    return 0;
                }
                if(!(board.Board::checkValidCol(start, end))){
                    return 0;
                }
            }
            else if(end.x == start.x + 1 && end.y == start.y - 1){
                if(board.Board::getPiece(end) == nullptr){
                    return 0;
                }
            }
            else if(end.x == start.x - 1 && end.y == start.y - 1){
                if(board.Board::getPiece(end) == nullptr){
                    return 0;
                }
            }
            else{
                return 0;
            }
    }
    return SUCCESS;
}
    


int Rook::validMove(Position start, Position end,
        const Board& board) const{ 
    if(board.Board::checkMoveRow(start, end)) {
        if (!(board.Board::checkValidRow(start, end))) {
            return 0;
        }
    } 
    else if (board.Board::checkMoveCol(start, end)) {
        if(!(board.Board::checkValidCol(start, end))) {
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
    if(board.Board::getPiece(end) != nullptr && board.Board::getPiece(end)->owner() == board.Board::getPiece(start)->owner()){
        return 0;
    }
    return SUCCESS; 
}

int Bishop::validMove(Position start, Position end,
        const Board& board) const {
   if(!(board.Board::checkMoveDia(start, end) && board.Board::checkValidDia(start, end))){
        return 0;
    }
    return SUCCESS; 
}

int Queen::validMove(Position start, Position end,
        const Board& board) const { 
    if(board.Board::checkMoveDia(start, end)){
        if(!board.Board::checkValidDia(start, end)){
            return 0;
        }
    }
    else if(board.Board::checkMoveRow(start, end)) {
        if (!board.Board::checkValidRow(start, end)) {
            return 0;
        }
    } 
    else if (board.Board::checkMoveCol(start, end)) {
        if(!board.Board::checkValidCol(start, end)) {
            return 0;
        }
    }
    else{
        return 0;
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
    if(board.Board::checkKing(*this, end) == 0){
        return 0;
    }
    if(board.Board::getPiece(end)!=nullptr && board.Board::getPiece(end)->owner() == board.Board::playerTurn()){
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
        //initPiece(PAWN_ENUM, WHITE, Position(i, 1));
        initPiece(pieces[i], WHITE, Position(i, 0));
        initPiece(pieces[i], BLACK, Position(i, 7));
        //initPiece(PAWN_ENUM, BLACK, Position(i, 6));
    }
}

//Loads a game of specified format
bool ChessGame::loadGame() {
    Prompts::loadGame();
    std::string fileNameInput;
    std::cin >> fileNameInput;
    std::string line;
    std::ifstream myfile(fileNameInput);
    int bufint = 0;
    int bufnumplayer, bufnumpiece;
    if (myfile.is_open()){
        getline(myfile, line); //rid of 'chess' line
        getline(myfile, line); 
        for(int i = 0; i < line.length(); i++){
            bufint += (line[i] - '0') * pow(10,line.length()-1-i);
        }
        m_turn = bufint;
        while ( getline(myfile,line) ){
            bufnumplayer = line[0] - '0';
            bufnumpiece = line[5] - '0';
            initPiece(bufnumpiece, Player(bufnumplayer), Position(7-(line[3] - 49), line[2] - 97));
        }
        myfile.close();
    }
    else {
        Prompts::loadFailure();
        return 0;
    }
    printAllPieces();
    return 1;
}
