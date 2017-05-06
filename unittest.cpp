#include "Game.h"
#include "Chess.h"
#include "Prompts.h"

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
	if(!p->validMove(start, Position(5,4), chess)){
		std::cout << "here 2";
		return false;
	}
	if(!(p->validMove(start, Position(4,2), chess))){
		std::cout << "here 4";
		return false;
	}
	return true;
}

bool checkRookB(){
	ChessGame chess;
	Position start = Position(4,4);
	chess.initPiece(ROOK_ENUM, BLACK, start);
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
	}
	if(!(p->validMove(Position(6,4), start, chess))){
		std::cout << "here 3";
		return false;
	}
	if(!(p->validMove(start, Position(4,2), chess))){
		std::cout << "here 4";
		return false;
	}
	if(!p->validMove(Position(4,2), start, chess)){
		std::cout << "here 5";
		return false;
	}
	return true;
}

bool checkKnightW(){
	ChessGame chess;
	Position start = Position(4,4);
	chess.initPiece(KNIGHT_ENUM, WHITE, start);
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
	if(p->validMove(start, Position(4,3), chess)){
		std::cout << "here 5";
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
	if(!(p->validMove(start, Position(5,6), chess))){
		std::cout << "here 4";
		return false;
	}
	if(!(p->validMove(start, Position(6,5), chess))){
		std::cout << "here 10";
		return false;
	}
	if(!(p->validMove(start, Position(3,6), chess))){
		std::cout << "here 11";
		return false;
	}
	if(!(p->validMove(start, Position(2,5), chess))){
		std::cout << "here 12";
		return false;
	}
	if(!(p->validMove(start, Position(3,2), chess))){
		std::cout << "here 13";
		return false;
	}
	if(!(p->validMove(start, Position(2,3), chess))){
		std::cout << "here 14";
		return false;
	}
	if(!(p->validMove(start, Position(5,2), chess))){
		std::cout << "here 15";
		return false;
	}
	if(!(p->validMove(start, Position(6,3), chess))){
		std::cout << "here 16";
		return false;
	}
	return true;
}


bool checkKnightB(){
	ChessGame chess;
	Position start = Position(4,4);
	chess.initPiece(KNIGHT_ENUM, BLACK, start);
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
	if(p->validMove(start, Position(4,3), chess)){
		std::cout << "here 5";
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
	if(!(p->validMove(start, Position(5,6), chess))){
		std::cout << "here 4";
		return false;
	}
	if(!(p->validMove(start, Position(6,5), chess))){
		std::cout << "here 10";
		return false;
	}
	if(!(p->validMove(start, Position(3,6), chess))){
		std::cout << "here 11";
		return false;
	}
	if(!(p->validMove(start, Position(2,5), chess))){
		std::cout << "here 12";
		return false;
	}
	if(!(p->validMove(start, Position(3,2), chess))){
		std::cout << "here 13";
		return false;
	}
	if(!(p->validMove(start, Position(2,3), chess))){
		std::cout << "here 14";
		return false;
	}
	if(!(p->validMove(start, Position(5,2), chess))){
		std::cout << "here 15";
		return false;
	}
	if(!(p->validMove(start, Position(6,3), chess))){
		std::cout << "here 16";
		return false;
	}
	return true;
}

bool checkBishopW(){
	ChessGame chess;
	Position start = Position(4,4);
	chess.initPiece(BISHOP_ENUM, WHITE, start);
	Piece* p = chess.Board::getPiece(start);
	if(!p->validMove(start, Position(7,7), chess)){
		std::cout << "here 1";
		return false;
	}
	if(p->validMove(start, Position(5,4), chess)){
		std::cout << "here 2";
		return false;
	}
	if(!p->validMove(start, Position(6,2), chess)){
		std::cout << "here 3";
		return false;
	}
	if(p->validMove(start, Position(4,3), chess)){
		std::cout << "here 5";
		return false;
	}
	if(!p->validMove(start, Position(1,1), chess)){
		std::cout << "here 6";
		return false;
	}
	if(p->validMove(start, Position(3,4), chess)){
		std::cout << "here 7";
		return false;
	}
	if(!p->validMove(start, Position(3,5), chess)){
		std::cout << "here 8";
		return false;
	}
	if((p->validMove(start, Position(4,5), chess))){
		std::cout << "here 4";
		return false;
	}
	return true;
}

bool checkBishopB(){
	ChessGame chess;
	Position start = Position(4,4);
	chess.initPiece(BISHOP_ENUM, BLACK, start);
	Piece* p = chess.Board::getPiece(start);
	if(!p->validMove(start, Position(7,7), chess)){
		std::cout << "here 1";
		return false;
	}
	if(p->validMove(start, Position(7,4), chess)){
		std::cout << "here 2";
		return false;
	}
	if(!p->validMove(start, Position(5,3), chess)){
		std::cout << "here 3";
		return false;
	}
	if(p->validMove(start, Position(4,1), chess)){
		std::cout << "here 5";
		return false;
	}
	if(!p->validMove(start, Position(1,1), chess)){
		std::cout << "here 6";
		return false;
	}
	if(p->validMove(start, Position(1,4), chess)){
		std::cout << "here 7";
		return false;
	}
	if(!p->validMove(start, Position(3,5), chess)){
		std::cout << "here 8";
		return false;
	}
	if((p->validMove(start, Position(4,7), chess))){
		std::cout << "here 4";
		return false;
	}
	return true;
}

bool checkQueenW(){
	ChessGame chess;
	Position start = Position(4,4);
	chess.initPiece(QUEEN_ENUM, WHITE, start);
	Piece* p = chess.Board::getPiece(start);
	if(!p->validMove(start, Position(7,7), chess)){
		std::cout << "here 1";
		return false;
	}
	if(!p->validMove(start, Position(7,4), chess)){
		std::cout << "here 2";
		return false;
	}
	if(!p->validMove(start, Position(5,3), chess)){
		std::cout << "here 3";
		return false;
	}
	if(!p->validMove(start, Position(4,1), chess)){
		std::cout << "here 5";
		return false;
	}
	if(!p->validMove(start, Position(1,1), chess)){
		std::cout << "here 6";
		return false;
	}
	if(!p->validMove(start, Position(1,4), chess)){
		std::cout << "here 7";
		return false;
	}
	if(!p->validMove(start, Position(3,5), chess)){
		std::cout << "here 8";
		return false;
	}
	if(!(p->validMove(start, Position(4,7), chess))){
		std::cout << "here 4";
		return false;
	}
	return true;
}

bool checkQueenB(){
	ChessGame chess;
	Position start = Position(4,4);
	chess.initPiece(QUEEN_ENUM, BLACK, start);
	Piece* p = chess.Board::getPiece(start);
	if(!p->validMove(start, Position(7,7), chess)){
		std::cout << "here 1";
		return false;
	}
	if(!p->validMove(start, Position(7,4), chess)){
		std::cout << "here 2";
		return false;
	}
	if(!p->validMove(start, Position(5,3), chess)){
		std::cout << "here 3";
		return false;
	}
	if(!p->validMove(start, Position(4,1), chess)){
		std::cout << "here 5";
		return false;
	}
	if(!p->validMove(start, Position(1,1), chess)){
		std::cout << "here 6";
		return false;
	}
	if(!p->validMove(start, Position(1,4), chess)){
		std::cout << "here 7";
		return false;
	}
	if(!p->validMove(start, Position(3,5), chess)){
		std::cout << "here 8";
		return false;
	}
	if(!(p->validMove(start, Position(4,7), chess))){
		std::cout << "here 4";
		return false;
	}
	return true;
}

bool checkKingW(){
	ChessGame chess;
	Position start = Position(4,4);
	chess.initPiece(KING_ENUM, WHITE, start);
	Piece* p = chess.Board::getPiece(start);
	if(!p->validMove(start, Position(5,5), chess)){
		std::cout << "here 1";
		return false;
	}
	if(!p->validMove(start, Position(5,4), chess)){
		std::cout << "here 2";
		return false;
	}
	if(!p->validMove(start, Position(5,3), chess)){
		std::cout << "here 3";
		return false;
	}
	if(!p->validMove(start, Position(4,3), chess)){
		std::cout << "here 5";
		return false;
	}
	if(!p->validMove(start, Position(3,3), chess)){
		std::cout << "here 6";
		return false;
	}
	if(!p->validMove(start, Position(3,4), chess)){
		std::cout << "here 7";
		return false;
	}
	if(!p->validMove(start, Position(3,5), chess)){
		std::cout << "here 8";
		return false;
	}
	if(!(p->validMove(start, Position(4,5), chess))){
		std::cout << "here 4";
		return false;
	}
	return true;
}

bool checkKingB(){
	ChessGame chess;
	Position start = Position(4,4);
	chess.initPiece(KING_ENUM, BLACK, start);
	Piece* p = chess.Board::getPiece(start);
	if(!p->validMove(start, Position(5,5), chess)){
		std::cout << "here 1";
		return false;
	}
	if(!p->validMove(start, Position(5,4), chess)){
		std::cout << "here 2";
		return false;
	}
	if(!p->validMove(start, Position(5,3), chess)){
		std::cout << "here 3";
		return false;
	}
	if(!p->validMove(start, Position(4,3), chess)){
		std::cout << "here 5";
		return false;
	}
	if(!p->validMove(start, Position(3,3), chess)){
		std::cout << "here 6";
		return false;
	}
	if(!p->validMove(start, Position(3,4), chess)){
		std::cout << "here 7";
		return false;
	}
	if(!p->validMove(start, Position(3,5), chess)){
		std::cout << "here 8";
		return false;
	}
	if(!(p->validMove(start, Position(4,5), chess))){
		std::cout << "here 4";
		return false;
	}
	return true;
}

int main() {
	if(!checkRow()){
		std::cout << "checkMoveRow() failed" << std::endl;
	}
	else if(!checkCol()){
		std::cout << "checkMoveCol() failed" << std::endl;
	}
	else if(!checkDia()){
		std::cout << "checkMoveDia() failed" << std::endl;
	}
	else if(!checkPawnW()){
		std::cout << "Pawn::validMove() on White failed" << std::endl;	
	}
	else if(!checkPawnB()){
		std::cout << "Pawn::validMove() on Black failed" << std::endl;	
	}
	else if(!checkRookW()){
		std::cout << "Rook::validMove() on White failed" << std::endl;	
	}
	else if(!checkRookB()){
		std::cout << "Rook::validMove() on Black failed" << std::endl;	
	}
	else if(!checkKnightW()){
		std::cout << "Knight::validMove() on White failed" << std::endl;	
	}
	else if(!checkKnightB()){
		std::cout << "Knight::validMove() on Black failed" << std::endl;	
	}
	else if(!checkBishopW()){
		std::cout << "Bishop::validMove() on White failed" << std::endl;	
	}
	else if(!checkBishopB()){
		std::cout << "Bishop::validMove() on Black failed" << std::endl;	
	}
	else if(!checkQueenW()){
		std::cout << "Queen::validMove() on White failed" << std::endl;	
	}
	else if(!checkQueenB()){
		std::cout << "Queen::validMove() on Black failed" << std::endl;	
	}
	else if(!checkKingW()){
		std::cout << "King::validMove() on White failed" << std::endl;	
	}
	else if(!checkKingB()){
		std::cout << "King::validMove() on Black failed" << std::endl;	
	}
	else{
		std::cout <<"Passed all unit tests" << std::endl;
	}
}