#undef FOR_RELEASE

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Game.h"
#include "Chess.h"
#include "Prompts.h"

///////////////
// Piece //
///////////////


int Piece::checkRow(Position start, Position end) const {
    int x = start.x;
    for(int i = start.y; i < end.y; i++) {
        if(Board::getPiece(Position(x,i)) != nullptr) {
            Prompts::invalidMove();
            return -1;
        }
    }
    return 0;
}