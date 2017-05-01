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
        for(unsigned int i = start.y+1; i < end.y; i++){

            if(Board::getPiece(Position(start.x, i)) != nullptr){
                return 0;
            }
        }
    }
    else {
        for(unsigned int i = end.y+1; i < start.y; i++){
            if(Board::getPiece(Position(start.x, i)) != nullptr){
                return 0;
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
        for(unsigned int i = start.x+1; i < end.x; i++){
            if(Board::getPiece(Position(i, start.y)) != nullptr){
                return 0;
            }
        }
    }
    else {
        for(unsigned int i = end.x+1; i < start.x; i++){
            if(Board::getPiece(Position(i, start.y)) != nullptr){
                return 0;
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
        for(unsigned int i = 1; i < (end.x - start.x); i++){
            if(Board::getPiece(Position(start.x + i, start.y + i)) != nullptr){
                return 0;
            }
        }
    }
    else if(right){
        for(int i = 1; i < (int)(end.x - start.x); i++){
            if(Board::getPiece(Position(start.x + i, start.y - i)) != nullptr){
                return 0;
            }
        }
    }
    else if(up){
        for(unsigned int i = 1; i < (end.y - start.y); i++){
            if(Board::getPiece(Position(start.x - i, start.y + i)) != nullptr){
                return 0;
            }
        }
    }
    else{
        for(int i = 1; i < (int)(start.y - end.y); i++){
            if(Board::getPiece(Position(start.x - i, start.y - i)) != nullptr){
                return 0;
            }
        }
    }
    return 1;
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
