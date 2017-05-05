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

bool Board::loadGame() {
    Prompts::loadGame();
    std::string fileNameInput;
    std::cin >> fileNameInput;
    std::string line;
    std::ifstream myfile(fileNameInput);
    if (myfile.is_open()){
        while ( getline(myfile,line) ){
            std::cout << line[0] << " ";
            std::cout << line[2] << " ";
            std::cout << line[7] << '\n';
        }
        myfile.close();
    }
   /* for (size_t i = 0; i < pieces.size(); ++i) {
        initPiece(PAWN_ENUM, WHITE, Position(i, 1));
        initPiece(pieces[i], WHITE, Position(i, 0));
        initPiece(pieces[i], BLACK, Position(i, 7));
        initPiece(PAWN_ENUM, BLACK, Position(i, 6));
    }*/

}

void Board::gameOptions(){
    int input = 0;
    Prompts::menu();
    while(!(std::cin >> input)){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        Prompts::menu();
    }
    if(input == 2){
        Board::loadGame();
    }
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

bool Board::saveGame() const{
    std::string fileName;
    Prompts::saveGame();
    std::cin >> fileName;
    std::ofstream myfile (fileName + ".txt");
    char bufferx;
    if (myfile.is_open()){
        myfile << "chess\n";
        myfile << Board::turn()-1 << std::endl;
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                if(Board::getPiece(Position(j, i))) {
                    int x =  i + 97;
                    itoa(x,bufferx,10);
                    myfile << Board::getPiece(Position(j,i))->owner()
                    << " " << bufferx << j << " "
                    << Board::getPiece(Position(j,i))->id()
                    << std::endl;
                }
            }
        }
        myfile.close();
    }
    else Prompts::saveGame();
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
    Piece *a;
    while(i <= 7 && j <= 7 && a == nullptr){
        a = Board::getPiece(Position(i,j));
        i++;
        j++;
    }
    if(!(a == nullptr)){
        if((a->id() == 3 || a->id() == 4 || a->id() == 0) && a->owner() != king.owner()){
            if(a->id() == 0){
                if(Board::getPiece(Position(end.x+1,end.y+1))){
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
                if(Board::getPiece(Position(end.x-1,end.y+1))){
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
                if(Board::getPiece(Position(end.x+1,end.y-1))){
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
                if(Board::getPiece(Position(end.x-1,end.y-1))){
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
    if(!(a == nullptr)){
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
                    if(Board::getPiece(Position(i, j)) ->owner() == BLACK){
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
        Prompts::check(BLACK);
        return 1;
    }
    else if(Board::checkKing(*kb, kbs) == 0){
        Prompts::check(WHITE);
    }
    return -1;

}
