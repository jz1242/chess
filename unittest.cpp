#include "Game.h"
#include "Chess.h"
#include "Prompts.h"

//TODO check Board::validPosition()

/*Test Chess.cpp files*/

bool checkRow(){
	ChessGame chess;
	if(chess.Board::checkMoveRow(Position(4,4), Position(5,5))){
		std::cout << "here 1";
		return false;
	}
	if(chess.Board::checkMoveRow(Position(4,4), Position(4,4))){
		std::cout << "here 2";
		return false;
	}
	if(chess.Board::checkMoveRow(Position(4,4), Position(5,3))){
		std::cout << "here 3";
		return false;
	}
	if(chess.Board::checkMoveRow(Position(4,4), Position(4,3))){
		std::cout << "here 4";
		return false;
	}
	if(chess.Board::checkMoveRow(Position(4,4), Position(3,3))){
		std::cout << "here 5";
		return false;
	}
	if(!chess.Board::checkMoveRow(Position(4,4), Position(3,4))){
		std::cout << "here 6";
		return false;
	}
	if(chess.Board::checkMoveRow(Position(4,4), Position(3,5))){
		std::cout << "here 7";
		return false;
	}
	if(chess.Board::checkMoveRow(Position(4,4), Position(4,5))){
		std::cout << "here 8";
		return false;
	}
	if(!chess.Board::checkMoveRow(Position(4,4), Position(5,4))){
		std::cout << "here 9";
		return false;
	}
	if(!chess.Board::checkMoveRow(Position(5,4), Position(4,4))){
		std::cout << "here 10";
		return false;
	}
	return true;
}

bool checkCol(){
	ChessGame chess;
	if(chess.Board::checkMoveCol(Position(4,4), Position(5,5))){
		std::cout << "here 1";
		return false;
	}
	if(chess.Board::checkMoveCol(Position(4,4), Position(4,4))){
		std::cout << "here 2";
		return false;
	}
	if(chess.Board::checkMoveCol(Position(4,4), Position(5,4))){
		std::cout << "here 9";
		return false;
	}
	if(chess.Board::checkMoveCol(Position(4,4), Position(5,3))){
		std::cout << "here 3";
		return false;
	}
	if(chess.Board::checkMoveCol(Position(4,4), Position(3,3))){
		std::cout << "here 5";
		return false;
	}
	if(chess.Board::checkMoveCol(Position(4,4), Position(3,4))){
		std::cout << "here 6";
		return false;
	}
	if(chess.Board::checkMoveCol(Position(4,4), Position(3,5))){
		std::cout << "here 7";
		return false;
	}
	if(!chess.Board::checkMoveCol(Position(4,4), Position(4,3))){
		std::cout << "here 4";
		return false;
	}
	if(!chess.Board::checkMoveCol(Position(4,3), Position(4,4))){
		std::cout << "here 4";
		return false;
	}
	return true;
}


bool checkDia(){
	ChessGame chess;
	if(!chess.Board::checkMoveDia(Position(1,1), Position(2,2))){
		return false;
	}
	if(chess.Board::checkMoveDia(Position(1,1), Position(1,2))){
		return false;
	}
	if(chess.Board::checkMoveDia(Position(2,2), Position(3,2))){
		return false;
	}
	if(!chess.Board::checkMoveDia(Position(2,2), Position(5,5))){
		return false;
	}
	if(!chess.Board::checkMoveDia(Position(4,4), Position(1,1))){
		return false;
	}
	if(!chess.Board::checkMoveDia(Position(3,3), Position(5,1))){
		return false;
	}
	if(!chess.Board::checkMoveDia(Position(3,3), Position(1,5))){
		return false;
	}
	return true;
}

bool checkPawnW(){
	ChessGame chess;
	Position start = Position(4,4);
	chess.initPiece(PAWN_ENUM, WHITE, start);
	Piece* p = chess.Board::getPiece(start);
	if(p->validMove(start, Position(5,5), chess)){
		return false;
	}
	if(p->validMove(start, Position(5,4), chess)){
		return false;
	}
	if(p->validMove(start, Position(5,3), chess)){
		return false;
	}
	if(p->validMove(start, Position(4,3), chess)){
		return false;
	}
	if(p->validMove(start, Position(3,3), chess)){
		return false;
	}
	if(p->validMove(start, Position(3,4), chess)){
		return false;
	}
	if(p->validMove(start, Position(3,5), chess)){
		return false;
	}
	if(!p->validMove(start, Position(4,5), chess)){
		return false;
	}
	/*
	if(chess.ChessGame::makeMove(Position(1,1), Position(0,1)) >= 0){
		return false;
	}
	if(chess.ChessGame::makeMove(Position(1,1), Position(0,2)) >= 0){
		return false;
	}
	if(chess.ChessGame::makeMove(Position(1,1), Position(1,2)) != 0){
		return false;
	}*/
	return true;
}

bool checkPawnB(){
	ChessGame chess;
	Position start = Position(4,4);
	chess.initPiece(PAWN_ENUM, BLACK, start);
	Piece* p = chess.Board::getPiece(start);
	if(p->validMove(start, Position(5,5), chess)){
		std::cout << "here 1";
		return false;
	}
	if(p->validMove(start, Position(5,4), chess)){
		std::cout << "here 2";
		return false;
	}
	if(p->validMove(start, Position(5,3), chess)){
		std::cout << "here 3";
		return false;
	}
	if(p->validMove(start, Position(3,3), chess)){
		std::cout << "here 5";
		return false;
	}
	if(p->validMove(start, Position(3,4), chess)){
		std::cout << "here 6";
		return false;
	}
	if(p->validMove(start, Position(3,5), chess)){
		std::cout << "here 7";
		return false;
	}
	if(p->validMove(start, Position(4,5), chess)){
		std::cout << "here 8";
		return false;
	}
	if(!(p->validMove(start, Position(4,3), chess))){
		std::cout << "here 4";
		return false;
	}
	return true;
}

bool checkRookW(){
	ChessGame chess;
	Position start = Position(4,4);
	chess.initPiece(ROOK_ENUM, WHITE, start);
	Piece* p = chess.Board::getPiece(start);
	if(p->validMove(start, Position(5,5), chess)){
		std::cout << "here 1";
		return false;
	}
	if(p->validMove(start, Position(5,3), chess)){
		std::cout << "here 5";
		return false;
	}
	if(p->validMove(start, Position(3,3), chess)){
		std::cout << "here 7";
		return false;
	}
	if(p->validMove(start, Position(3,5), chess)){
		std::cout << "here 8";
		return false;
	}
	if(!p->validMove(start, Position(6,4), chess)){
		std::cout << "here 2";
		return false;
	}/*
	std::cout << (p->validMove(Position(6,4), start, chess));
	if(!(p->validMove(Position(6,4), start, chess))){
		std::cout << "here 3";
		return false;
	}*/
	if(!(p->validMove(start, Position(4,2), chess))){
		std::cout << "here 4";
		return false;
	}/*
	if(!p->validMove(Position(4,2), start, chess)){
		std::cout << "here 2";
		return false;
	}*/
	return true;
}

int main() {
	if(!checkRow()){
		std::cout << "checkMoveRow() failed" << std::endl;
	}
	if(!checkCol()){
		std::cout << "checkMoveCol() failed" << std::endl;
	}
	if(!checkDia()){
		std::cout << "checkMoveDia() failed" << std::endl;
	}
	if(!checkPawnW()){
		std::cout << "Pawn::validMove() on White failed" << std::endl;	
	}
	if(!checkPawnB()){
		std::cout << "Pawn::validMove() on Black failed" << std::endl;	
	}
	if(!checkRookW()){
		std::cout << "Rook::validMove() on White failed" << std::endl;	
	}
	else{
		std::cout <<"Passed all unit tests" << std::endl;
	}
}