#include <assert.h>
#include <cctype>
#include <iostream>

#include "Game.h"
#include "Prompts.h"

///////////////
// Board //
///////////////

Board::~Board() {
    // Delete all pointer-based resources
    for (unsigned int i=0; i < m_width * m_height; i++)
        delete m_pieces[i];
    for (size_t i=0; i < m_registeredFactories.size(); i++)
        delete m_registeredFactories[i];
}

// Get the Piece at a specific Position, or nullptr if there is no
// Piece there or if out of bounds.
Piece* Board::getPiece(Position position) const {
    if (validPosition(position))
        return m_pieces[index(position)];
    else {
        Prompts::outOfBounds();
        return nullptr;
    }
}

// Create a piece on the board using the factory.
// Returns true if the piece was successfully placed on the board
bool Board::initPiece(int id, Player owner, Position position) {
    Piece* piece = newPiece(id, owner);
    if (!piece) return false;

    // Fail if the position is out of bounds
    if (!validPosition(position)) {
        Prompts::outOfBounds();
        return false;
    }
    // Fail if the position is occupied
    if (getPiece(position)) {
        Prompts::blocked();
        return false;
    }
    m_pieces[index(position)] = piece;
    return true;
}

// Add a factory to the Board to enable producing
// a certain type of piece
bool Board::addFactory(AbstractPieceFactory* pGen) {
    // Temporary piece to get the ID
    Piece* p = pGen->newPiece(WHITE);
    int id = p->id();
    delete p;

    PieceGenMap::iterator it = m_registeredFactories.find(id);
    if (it == m_registeredFactories.end()) { // not found
        m_registeredFactories[id] = pGen;
        return true;
    } else {
        std::cout << "Id " << id << " already has a generator\n";
        return false;
    }
}

// Search the factories to find a factory that can translate `id' to
// a Piece, and use it to create the Piece. Returns nullptr if not found.
Piece* Board::newPiece(int id, Player owner) {
    PieceGenMap::iterator it = m_registeredFactories.find(id);
    if (it == m_registeredFactories.end()) { // not found
        std::cout << "Id " << id << " has no generator\n";
        return nullptr;
    } else {
        return it->second->newPiece(owner);
    }
}

int Board::checkValidRow(Position start, Position end) const {
    int moveToRight = 0;
    if(start.y < end.y){
        moveToRight  = 1;
    }
    if(moveToRight) {
        for(unsigned int i = start.y+1; i <= end.y; i++){
            if(Board::getPiece(Position(start.x, i)) != nullptr){
                if(!(i == end.y && Board::getPiece(Position(start.x, i))->owner() != playerTurn())){
                    return 0;
                }
            }
        }
    }
    else {
        for(unsigned int i = start.y - 1; i >= end.y; i--){
            if(Board::getPiece(Position(start.x, i)) != nullptr){
                if(!(i == end.y && Board::getPiece(Position(start.x, i))->owner() != playerTurn())){
                    return 0;
                }
            }
        }
    }
    return 1;
}

int Board::checkValidCol(Position start, Position end) const {
    int moveUp = 0;
    if(start.x < end.x){
        moveUp = 1;
    }
    if(moveUp) {
        for(unsigned int i = start.x+1; i <= end.x; i++){
            if(Board::getPiece(Position(i, start.y)) != nullptr){
                if(!(i == end.x && Board::getPiece(Position(i, start.y))->owner() != playerTurn())){
                    return 0;
                }
            }
        }
    }
    else {
        for(unsigned int i = start.x - 1; i >= end.x; i--){
            if(Board::getPiece(Position(i, start.y)) != nullptr){
                if(!(i == end.x && Board::getPiece(Position(i, start.y))->owner() != playerTurn())){
                    return 0;
                }
            }
        }
    }
    return 1;
}
int Board::checkValidDia(Position start, Position end) const {
    int right = 0;
    if(start.x < end.x){
        right = 1;
    }
    int up = 0;
    if(start.y < end.y){
        up = 1;
    }
    if(right && up){
        for(unsigned int i = 1; i <= (end.x - start.x); i++){
            if(Board::getPiece(Position(start.x + i, start.y + i)) != nullptr){
                if(!(i == (end.x - start.x) && Board::getPiece(Position(start.x + i, start.y + i))->owner() != playerTurn())){
                    return 0;
                }
            }
        }
    }
    else if(right){
        for(int i = 1; i <= (int)(end.x - start.x); i++){
            if(Board::getPiece(Position(start.x + i, start.y - i)) != nullptr){
                if(!(i == (end.x - start.x) && Board::getPiece(Position(start.x + i, start.y - i))->owner() != playerTurn())){
                    return 0;
                }
            }
        }
    }
    else if(up){
        for(unsigned int i = 1; i <= (end.y - start.y); i++){
            if(Board::getPiece(Position(start.x - i, start.y + i)) != nullptr){
                if(!(i == (end.x - start.x) && Board::getPiece(Position(start.x - i, start.y + i))->owner() != playerTurn())){
                    return 0;
                }
            }
        }
    }
    else{
        for(int i = 1; i <= (int)(start.y - end.y); i++){
            if(Board::getPiece(Position(start.x - i, start.y - i)) != nullptr){
                if(!(i == (end.x - start.x) && Board::getPiece(Position(start.x - i, start.y - i))->owner() != playerTurn())){
                    return 0;
                }
            }
        }
    }
    return 1;
}

void Board::promote(Position end) {
    if(Board::getPiece(end)->owner() == 0) {
        if(end.y == 7){
            m_pieces[index(end)] = nullptr;
            initPiece(4, Player(0), end);
        }
        if(end.y == 0){
            m_pieces[index(end)] = nullptr;
            initPiece(4, Player(1), end);
        }
    }
}
void Board::printAllPieces() const{
    //std::cout<<i<<" "<<j<<std::endl;
    for(int i = 7; i >= 0; i--){
        for(int j = 0; j <= 7; j++){
            Piece* a = Board::getPiece(Position(j, i));
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

int Board::checkKing(Piece king, Position end) const{
    int i = end.x + 1;
    int j = end.y + 1;
    Piece *a = nullptr;
    while(i <= 7 && j <= 7 && a == nullptr){
        a = Board::getPiece(Position(i,j));
        i++;
        j++;
    }
    if(!(a == nullptr)){
        if((a->id() == 3 || a->id() == 4 || a->id() == 0) && a->owner() != king.owner()){
            if(a->id() == 0){
                if(Board::getPiece(Position(end.x+1,end.y+1)) == a){

                    return 0;
                }
            }
            else{
                return 0;
            }

        }
    }
    i = end.x - 1;
    j = end.y + 1;
    a = nullptr;
   while(i >= 0 && j <= 7 && a == nullptr){
        a = Board::getPiece(Position(i,j));
        i--;
        j++;
    }
    if(!(a == nullptr)){
        if((a->id() == 3 || a->id() == 4 || a->id() == 0) && a->owner() != king.owner()){
            if(a->id() == 0){
                if(Board::getPiece(Position(end.x-1,end.y+1)) == a){
                    return 0;
                }
            }
            else{
                return 0;
            }

        }
    }

    i = end.x + 1;
    j = end.y - 1;
    a = nullptr;
   while(i <= 7 && j >= 0 && a == nullptr){
        a = Board::getPiece(Position(i,j));
        i++;
        j--;
    }
    if(!(a == nullptr)){
        if((a->id() == 3 || a->id() == 4 || a->id() == 0) && a->owner() != king.owner()){
            if(a->id() == 0){
                if(Board::getPiece(Position(end.x+1,end.y-1)) == a){
                    return 0;
                }
            }
            else{
                return 0;
            }

        }
    }

    i = end.x - 1;
    j = end.y - 1;
    a = nullptr;
    while(i >= 0 && j >= 0 && a == nullptr){
        a = Board::getPiece(Position(i,j));
        i--;
        j--;
    }
    if(!(a == nullptr)){
        if((a->id() == 3 || a->id() == 4 || a->id() == 0) && a->owner() != king.owner()){
            if(a->id() == 0){
                if(Board::getPiece(Position(end.x-1,end.y-1)) == a){
                    return 0;
                }
            }
            else{
                return 0;
            }

        }
    }
    i = end.x + 1;
    a = nullptr;
    while(i <= 7 && a == nullptr){
        a = Board::getPiece(Position(i,end.y));
        i++;
    }
    if(!(a == nullptr)){
        if((a->id() == 1 || a->id() == 4) && a->owner() != king.owner()){
            return 0;
        }
    }

    i = end.x - 1;
    a = nullptr;
    while(i >= 0 && a == nullptr){
        a = Board::getPiece(Position(i,end.y));
        i--;
    }
    if(!(a == nullptr)){
        if((a->id() == 1 || a->id() == 4) && a->owner() != king.owner()){
            return 0;
        }
    }

    i = end.y + 1;
    a = nullptr;
    while(i <= 7 && a == nullptr){
        a = Board::getPiece(Position(end.x,i));
        i++;
    }
    if(!(a == nullptr)){
        if((a->id() == 1 || a->id() == 4) && a->owner() != king.owner()){
            return 0;
        }
    }

    i = end.y - 1;
    a = nullptr;
    while(i >= 0 && a == nullptr){
        a = Board::getPiece(Position(end.x,i));
        i--;
    }
    if(a != nullptr){
        if((a->id() == 1 || a->id() == 4) && a->owner() != king.owner()){
            return 0;
        }
    }
    int x = end.x;
    int y = end.y;

    if(y + 2 <=7 && x + 1 <=7 && Board::getPiece(Position(end.x + 1, end.y + 2)) != nullptr && Board::getPiece(Position(end.x + 1, end.y + 2))->id() == 2 && Board::getPiece(Position(end.x + 1, end.y + 2))->owner() != king.owner()){

        return 0;
    }
    if(y + 2 <=7 && x - 1 >= 0 && Board::getPiece(Position(end.x - 1, end.y + 2))!= nullptr && Board::getPiece(Position(end.x - 1, end.y + 2))->id() == 2 && Board::getPiece(Position(end.x - 1, end.y + 2))->owner() != king.owner()){

        return 0;
    }
    if(y - 2 >=0 && x + 1 <= 7 && Board::getPiece(Position(end.x + 1, end.y - 2))!= nullptr && Board::getPiece(Position(end.x + 1, end.y - 2))->id() == 2 && Board::getPiece(Position(end.x + 1, end.y - 2))->owner() != king.owner()){

        return 0;
    }
    if(y - 2 >= 0 && x - 1 >= 0 && Board::getPiece(Position(end.x - 1, end.y - 2))!= nullptr && Board::getPiece(Position(end.x - 1, end.y - 2))->id() == 2 && Board::getPiece(Position(end.x - 1, end.y - 2))->owner() != king.owner()){

        return 0;
    }
    if(y + 1 <=7 && x + 2 <= 7 && Board::getPiece(Position(end.x + 2, end.y + 1))!= nullptr && Board::getPiece(Position(end.x + 2, end.y + 1))->id() == 2 && Board::getPiece(Position(end.x + 2, end.y + 1))->owner() != king.owner()){

        return 0;
    }
    if(y + 1 <=7 && x - 2 >= 0 && Board::getPiece(Position(end.x - 2, end.y + 1))!= nullptr && Board::getPiece(Position(end.x - 2, end.y + 1))->id() == 2 && Board::getPiece(Position(end.x - 2, end.y + 1))->owner() != king.owner()){
        return 0;
    }
    if(y - 1 >= 0 && x + 2 <=7 && Board::getPiece(Position(end.x + 2, end.y - 1))!= nullptr && Board::getPiece(Position(end.x + 2, end.y - 1))->id() == 2 && Board::getPiece(Position(end.x + 2, end.y - 1))->owner() != king.owner()){

        return 0;
    }
    if(y - 1 >= 0 && x -2 >= 0 && Board::getPiece(Position(end.x - 2, end.y - 1))!= nullptr && Board::getPiece(Position(end.x - 2, end.y - 1))->id() == 2 && Board::getPiece(Position(end.x - 2, end.y - 1))->owner() != king.owner()){

        return 0;
    }
    return 1;
}
int Board::inCheck(){
    Piece* kw;
    Piece* kb;
    Position kbs;
    Position kws;
    for(int i = 0; i <=7; i++){
        for(int j = 0; j<=7; j++){
            if(Board::getPiece(Position(i, j)) != nullptr){
                if(Board::getPiece(Position(i, j)) -> id() == 5){
                    if(Board::getPiece(Position(i, j)) ->owner() == WHITE){
                        kw = Board::getPiece(Position(i, j));
                        kws = Position(i, j);
                    }
                    else{
                        kb = Board::getPiece(Position(i, j));
                        kbs = Position(i, j);
                    }
                }
            }

        }
    }

    if(Board::checkKing(*kw, kws) == 0){
        if(Board::checkMovesKing(kws) > 0){
            Prompts::check(BLACK);
        }
        else{
            //checkMovesOtherPieces(kw);
            Prompts::checkMate(BLACK);
        }

        return 1;
    }
    else if(Board::checkKing(*kb, kbs) == 0){
        if(Board::checkMovesKing(kbs) > 0){
            Prompts::check(WHITE);
        }
        else{
            Prompts::checkMate(WHITE);
        }
        return 1;
    }
    return -1;

}
int Board::checkMovesKing(Position start){
    int tot = 0;
    Piece* k = Board::getPiece(start);
    int i = start.x;
    int j = start.y;
    if(i + 1 <= 7 && j + 1 <=7){
        k = Board::getPiece(start);
        tot += Board::checkKing(*k, Position(i+1, j+1));
    }
    if(i - 1 >= 0 && j + 1 <=7){
        k = Board::getPiece(start);
        tot += Board::checkKing(*k, Position(i-1, j+1));
    }
    if(i + 1 <= 7 && j - 1 >= 0){
        k = Board::getPiece(start);
        tot += Board::checkKing(*k, Position(i+1, j-1));
    }
    if(i - 1 >= 0 && j - 1 >= 0){
        k = Board::getPiece(start);
        tot += Board::checkKing(*k, Position(i-1, j-1));
    }
    if(i + 1 <= 7){
        k = Board::getPiece(start);
        tot += Board::checkKing(*k, Position(i+1, j));
    }
    if(i - 1 >= 0){
        k = Board::getPiece(start);
        tot += Board::checkKing(*k, Position(i-1, j));
    }

    if(j + 1 <= 7){
        k = Board::getPiece(start);
        tot += Board::checkKing(*k, Position(i, j+1));
    }
    if(j - 1 >= 0){
        k = Board::getPiece(start);
        tot += Board::checkKing(*k, Position(i, j-1));
    }
    return tot;
}
int Board::checkMovesOtherPieces(Piece* k){
    int move = 0;
    for(int i = 0; i <= 7; i++){
        for(int j = 0; j <= 7; j++){
            Piece* a = Board::getPiece(Position(i,j));
            if(a != nullptr){
                if(a->owner() == k->owner()){
                    if(a->id() == 0){
                        move += Board::checkMovesPawn(Position(i,j));
                    }
                    if(a->id() == 1){
                        move += Board::checkMovesRook(Position(i,j));
                    }
                    if(a->id() == 2){
                        move += Board::checkMovesKnight(Position(i,j));
                    }
                    if(a->id() == 3){
                        move += Board::checkMovesBishop(Position(i,j));
                    }
                    if(a->id() == 4){
                        move += Board::checkMovesQueen(Position(i,j));
                    }
                }
            }
        }
    }

    return move;
}
int Board::checkMovesPawn(Position start){
    Piece* p = Board::getPiece(Position(start));
    int ret = -1;
    int i = start.x;
    int j = start.y;
    if(Board::validPosition(Position(i,j+1)) && p->validMove(start,Position(i,j+1), *this)){
        Board::makeMove(start, Position(i, j+1));
        if(inCheck() == -1){
            ret = 1;
        }
        Board::makeMove(Position(i, j+1), start);
    }
    if(Board::validPosition(Position(i+1,j+1)) && p->validMove(start, Position(i+1,j+1), *this)){
        Board::makeMove(start, Position(i+1, j+1));
        if(inCheck() == -1){
            ret = 1;
        }
        Board::makeMove( Position(i+1, j+1), start);
    }
    if(Board::validPosition(Position(i-1,j+1)) && p->validMove(start, Position(i-1,j+1), *this)){
        Board::makeMove(start, Position(i-1, j+1));
        if(inCheck() == -1){
            ret = 1;
        }
        Board::makeMove(Position(i-1, j+1), start);
    }

    return ret;
}
int Board::checkMovesRook(Position start){
    Piece* p = Board::getPiece(Position(start));
    int ret = -1;
    int x = start.x + 1;
    int y = start.y + 1;

    for(int i = x; i<=7; i++){
        if(p->validMove(start, Position(i, start.y), *this)){
            Board::makeMove(start, Position(i, start.y));
            if(inCheck() == -1){
                ret = 1;
            }
            Board::makeMove(Position(i, start.y),start);
        }

    }
    for(int i = y; i<=7; i++){
        if(p->validMove(start, Position(start.x, i), *this)){
            Board::makeMove(start, Position(start.x, i));
            if(inCheck() == -1){
                ret = 1;
            }
            Board::makeMove(Position(start.x, i),start);
        }

    }
    return ret;
}
int Board::checkMovesKnight(Position start){
    Piece* p = Board::getPiece(Position(start));
    int ret = -1;
    int x = start.x;
    int y = start.y;

    if(Board::validPosition(Position(x+1,y+2))){
        if(p->validMove(start, Position(x+1, y+2), *this)){
            Board::makeMove(start, Position(x+1, y+2));
            if(inCheck() == -1){
                ret = 1;
            }
            Board::makeMove(Position(x+1, y+2), start);
        }

    }
    if(Board::validPosition(Position(x-1, y+2))){
        if(p->validMove(start, Position(x-1, y+2), *this)){
            Board::makeMove(start, Position(x+1, y+2));
            if(inCheck() == -1){
                ret = 1;
            }
            Board::makeMove(Position(x+1, y+2), start);
        }
    }
    if(Board::validPosition(Position(x+1, y-2))){
        if(p->validMove(start, Position(x+1, y-2), *this)){
            Board::makeMove(start, Position(x+1, y-2));
            if(inCheck() == -1){
                ret = 1;
            }
            Board::makeMove(Position(x+1, y-2), start);
        }

        return 0;
    }
    if(Board::validPosition(Position(x-1, y-2))){
        if(p->validMove(start, Position(x-1, y-2), *this)){
            Board::makeMove(start, Position(x-1, y-2));
            if(inCheck() == -1){
                ret = 1;
            }
            Board::makeMove(Position(x-1, y-2), start);
        }
        return 0;
    }
    if(Board::validPosition(Position(x+2, y+1))){
        if(p->validMove(start, Position(x+2, y+1), *this)){
            Board::makeMove(start, Position(x+2, y+1));
            if(inCheck() == -1){
                ret = 1;
            }
            Board::makeMove(Position(x+2, y+1), start);
        }
    }
    if(Board::validPosition(Position(x-2, y+1))){
        if(p->validMove(start, Position(x-2, y+1), *this)){
            Board::makeMove(start, Position(x-2, y+1));
            if(inCheck() == -1){
                ret = 1;
            }
            Board::makeMove(Position(x-2, y+1), start);
        }
    }
    if(Board::validPosition(Position(x+2, y-1))){
        if(p->validMove(start, Position(x+2, y-1), *this)){
            Board::makeMove(start, Position(x+2, y-1));
            if(inCheck() == -1){
                ret = 1;
            }
            Board::makeMove(Position(x+2, y-1), start);
        }
    }
    if(Board::validPosition(Position(x-2, y-1))){
        if(p->validMove(start, Position(x-2, y-1), *this)){
            Board::makeMove(start, Position(x-2, y-1));
            if(inCheck() == -1){
                ret = 1;
            }
            Board::makeMove(Position(x-2, y-1), start);
        }
    }
    return ret;
}


int Board::checkMovesBishop(Position start){
    Piece* p = Board::getPiece(Position(start));
    int ret = -1;

    int i = start.x + 1;
    int j = start.y + 1;
    while(i <= 7 && j <= 7){
        if(p->validMove(start, Position(i,j), *this)){
            Board::makeMove(start, Position(i, j));
            if(inCheck() == -1){
                ret = 1;
            }
            Board::makeMove(Position(i, j), start);
        }
        i++;
        j++;
    }

   i = start.x - 1;
   j = start.y + 1;
   while(i >= 0 && j <= 7){
       if(p->validMove(start, Position(i,j), *this)){
           Board::makeMove(start, Position(i, j));
           if(inCheck() == -1){
               ret = 1;
           }
           Board::makeMove(Position(i, j), start);
       }
       i--;
       j++;
    }

   i = start.x + 1;
   j = start.y - 1;
   while(i <= 7 && j >= 0){
       if(p->validMove(start, Position(i,j), *this)){
           Board::makeMove(start, Position(i, j));
           if(inCheck() == -1){
               ret = 1;
           }
           Board::makeMove(Position(i, j), start);
       }
       i++;
       j--;
    }

    i = start.x - 1;
    j = start.y - 1;
    while(i >= 0 && j >= 0){
        if(p->validMove(start, Position(i,j), *this)){
            Board::makeMove(start, Position(i, j));
            if(inCheck() == -1){
                ret = 1;
            }
            Board::makeMove(Position(i, j), start);
        }
        i--;
        j--;
    }
    return ret;

}
int Board::checkMovesQueen(Position start){
    Piece* p = Board::getPiece(Position(start));
    int ret = -1;
    int x = start.x + 1;
    int y = start.y + 1;

    for(int i = x; i<=7; i++){
        if(p->validMove(start, Position(i, start.y), *this)){
            Board::makeMove(start, Position(i, start.y));
            if(inCheck() == -1){
                ret = 1;
            }
            Board::makeMove(Position(i, start.y),start);
        }

    }
    for(int i = y; i<=7; i++){
        if(p->validMove(start, Position(start.x, i), *this)){
            Board::makeMove(start, Position(start.x, i));
            if(inCheck() == -1){
                ret = 1;
            }
            Board::makeMove(Position(start.x, i),start);
        }

    }
    int i = start.x + 1;
    int j = start.y + 1;
    while(i <= 7 && j <= 7){
        if(p->validMove(start, Position(i,j), *this)){
            Board::makeMove(start, Position(i, j));
            if(inCheck() == -1){
                ret = 1;
            }
            Board::makeMove(Position(i, j), start);
        }
        i++;
        j++;
    }

   i = start.x - 1;
   j = start.y + 1;
   while(i >= 0 && j <= 7){
       if(p->validMove(start, Position(i,j), *this)){
           Board::makeMove(start, Position(i, j));
           if(inCheck() == -1){
               ret = 1;
           }
           Board::makeMove(Position(i, j), start);
       }
       i--;
       j++;
    }

   i = start.x + 1;
   j = start.y - 1;
   while(i <= 7 && j >= 0){
       if(p->validMove(start, Position(i,j), *this)){
           Board::makeMove(start, Position(i, j));
           if(inCheck() == -1){
               ret = 1;
           }
           Board::makeMove(Position(i, j), start);
       }
       i++;
       j--;
    }

    i = start.x - 1;
    j = start.y - 1;
    while(i >= 0 && j >= 0){
        if(p->validMove(start, Position(i,j), *this)){
            Board::makeMove(start, Position(i, j));
            if(inCheck() == -1){
                ret = 1;
            }
            Board::makeMove(Position(i, j), start);
        }
        i--;
        j--;
    }
    return ret;

}
