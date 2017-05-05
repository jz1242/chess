#include "Game.h"
#include "Chess.h"
#include "Prompts.h"

bool checkCol(){/*
	if(ChessGame::checkMoveRow(Position(1,2), Position(2,3))){
		return false;
	}
	if(checkMoveRow(Position(1,2), Position(2,2))){
		return false;
	}
	if(!checkMoveRow(Position(2,2), Position(2,3))){
		return false;
	}
	if(!checkMoveRow(Position(2,3), Position(2,3))){
		return false;
	}*/
	return true;
}

int main() {
	if(!checkCol()){
		std::cout << "checkMoveRow() failed" << std::endl;
	}
}