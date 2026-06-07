#ifndef PIECE_H
#define PIECE_H

#include "Typedefs.h"
#include <vector>
#include <memory>

class Board;

// Klasa reprezentujaca pojedynczy pionek na szachownicy
class Piece
{
    private:
        int x, y;      // Pozycja pionka
        bool isWhite;  // Kolor: true to biale, false to czarne
        bool isKing;   // Flaga czy pionek awansowal na damke

    public:
        // Konstruktor
        Piece(int x, int y, bool isWhite);

        // Pobieranie wspolrzednych X i Y
        coords_t getCoordinates() const;

        // Sprawdzanie koloru pionka
        bool isWhitePiece() const;

        // Sprawdzanie czy to damka
        bool isKingPiece() const;

        // Zmiana pozycji pionka
        void moveTo(int newX, int newY);

        // Sprawdzanie i zamiana pionka w damke
        void checkIfShouldBeKing(const Board& board);

        // Szukanie dostepnych ruchow dla tego pionka
        std::vector<move_ptr_t> getPossibleMoves(const Board& board) const;
};

#endif