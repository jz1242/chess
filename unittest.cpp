#include "Game.h"
#include "Chess.h"
#include "Prompts.h"

//TODO check Board::validPosition()

/*Test Chess.cpp files*/

bool checkRow(){
	ChessGame chess;
	if(chess.Board::checkMoveRow(Position(1,2), Position(2,3))){
		return false;
	}
	if(chess.Board::checkMoveRow(Position(1,2), Position(2,2))){
		return false;
	}
	if(!chess.Board::checkMoveRow(Position(2,2), Position(2,3))){
		return false;
	}
	if(!chess.Board::checkMoveRow(Position(2,3), Position(2,3))){
		return false;
	}
	return true;
}

bool checkCol(){
	ChessGame chess;
	if(chess.Board::checkMoveCol(Position(1,2), Position(2,3))){
		return false;
	}
	if(!chess.Board::checkMoveCol(Position(1,2), Position(2,2))){
		return false;
	}
	if(chess.Board::checkMoveCol(Position(2,2), Position(2,3))){
		return false;
	}
	if(!chess.Board::checkMoveCol(Position(2,3), Position(2,3))){
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
	chess.initPiece(PAWN_ENUM, WHITE, Position(1, 1));
	if(chess.ChessGame::makeMove(Position(1,1), Position(2,2)) >= 0){
		return false;
	}
	if(chess.ChessGame::makeMove(Position(1,1), Position(2,1)) >= 0){
		return false;
	}
	if(chess.ChessGame::makeMove(Position(1,1), Position(2,0)) >= 0){
		return false;
	}
	if(chess.ChessGame::makeMove(Position(1,1), Position(1,0)) >= 0){
		return false;
	}
	if(chess.ChessGame::makeMove(Position(1,1), Position(0,0)) >= 0){
		return false;
	}
	if(chess.ChessGame::makeMove(Position(1,1), Position(0,1)) >= 0){
		return false;
	}
	if(chess.ChessGame::makeMove(Position(1,1), Position(0,2)) >= 0){
		return false;
	}
	if(chess.ChessGame::makeMove(Position(1,1), Position(1,2)) != 0){
		return false;
	}
	return true;
}

bool checkPawnB(){
	ChessGame chess;
	chess.initPiece(PAWN_ENUM, BLACK, Position(6, 6));
	chess.printAllPieces();
	std::cout << std::endl;
	if(chess.ChessGame::makeMove(Position(6,6), Position(7,7)) >= 0){
		return false;
	}
	if(chess.ChessGame::makeMove(Position(6,6), Position(7,6)) >= 0){
		return false;
	}
	if(chess.ChessGame::makeMove(Position(6,6), Position(7,5)) >= 0){
		return false;
	}
	if(chess.ChessGame::makeMove(Position(6,6), Position(5,5)) >= 0){
		return false;
	}
	if(chess.ChessGame::makeMove(Position(6,6), Position(5,6)) >= 0){
		return false;
	}
	if(chess.ChessGame::makeMove(Position(6,6), Position(5,7)) >= 0){
		return false;
	}
	if(chess.ChessGame::makeMove(Position(6,6), Position(6,7)) >= 0){
		return false;
	}
	chess.printAllPieces();
	std::cout << "turn" << chess.turn();
	std::cout << chess.ChessGame::makeMove(Position(6,6), Position(6,5)) << std::endl;
	std::cout << chess.ChessGame::makeMove(Position(6,6), Position(6,5)) << std::endl;
	if(chess.ChessGame::makeMove(Position(6,6), Position(6,5)) != 0){
		chess.printAllPieces();
		std::cout << "8";
		return false;
	}
	return true;
}

bool checkRookW(){
	ChessGame chess;
	chess.initPiece(ROOK_ENUM, WHITE, Position(1, 1));
	chess.printAllPieces();
	std::cout << std::endl;
	if(chess.ChessGame::makeMove(Position(1,1), Position(2,2)) >= 0){
		std::cout << "1" << std::endl;
		return false;
	}
	if(chess.ChessGame::makeMove(Position(1,1), Position(0,0)) >= 0){
		std::cout << "2" << std::endl;
		return false;
	}
	if(chess.ChessGame::makeMove(Position(1,1), Position(0,2)) >= 0){
		std::cout << "3" << std::endl;
		return false;
	}
	if(chess.ChessGame::makeMove(Position(1,1), Position(2,0)) >= 0){
		std::cout << "4" << std::endl;
		return false;
	}
	if(chess.ChessGame::makeMove(Position(1,1), Position(7,1)) != 0){
		std::cout << "5" << std::endl;
		return false;
	}
	if(chess.ChessGame::makeMove(Position(7,1), Position(0,1)) != 0){
		std::cout << chess.ChessGame::makeMove(Position(7,1), Position(0,1));
		chess.printAllPieces();
		std::cout << "6" << std::endl;
		return false;
	}
	if(chess.ChessGame::makeMove(Position(0,1), Position(0,7)) != 0){
		std::cout << "7" << std::endl;
		return false;
	}
	if(chess.ChessGame::makeMove(Position(0,7), Position(0,0)) != 0){
		std::cout << "8" << std::endl;
		return false;
	}
	chess.printAllPieces();
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
	/*if(!checkPawnB()){
		std::cout << "Pawn::validMove() on Black failed" << std::endl;	
	}*/
	if(!checkRookW()){
		std::cout << "Rook::validMove() on White failed" << std::endl;	
	}
	else{
		std::cout <<"Passed all unit tests" << std::endl;
	}
}