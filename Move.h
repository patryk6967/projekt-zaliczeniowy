#ifndef MOVE_H
#define MOVE_H

#include "Typedefs.h"
#include <vector>

class Piece;
class Board;

// Klasa do przechowywania pojedynczego ruchu lub serii bic
class Move
{
    public:
        // Wspolrzedne poczatkowe (x1, y1) i koncowe (x2, y2)
        int x1, y1;
        int x2, y2;
        
        // Flaga czy ruch jest skokiem (biciem)
        bool isJump;
        
        // Wskaznik na poprzedni skok przy biciu wielokrotnym
        Move* precedingMove;

        // Konstruktor zwyklego ruchu albo pierwszego bicia
        Move(int x1, int y1, int x2, int y2, bool czySkok) : 
            x1(x1), y1(y1), x2(x2), y2(y2), isJump(czySkok), precedingMove(nullptr) {};
            
        // Konstruktor do kolejnego bicia w serii (bicie wielokrotne)
        Move(int x1, int y1, int x2, int y2, bool czySkok, Move* poprzedniRuch) : 
            x1(x1), y1(y1), x2(x2), y2(y2), isJump(czySkok), precedingMove(poprzedniRuch) {};

        // Pobieranie pozycji startowej
        coords_t getStartingPosition() const;

        // Pobieranie pozycji koncowej
        coords_t getEndingPosition() const;

        // Pobieranie listy wszystkich pionkow zbitych w tym ruchu
        std::vector<Piece*> getJumpedPieces(const Board& board) const;
};

#endif