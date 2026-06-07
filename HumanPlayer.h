#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "Player.h"
#include "Typedefs.h"
#include <vector>
#include <string>

class Board;
class Piece;

// Klasa do obslugi gracza-czlowieka
class HumanPlayer : public Player
{
    private:
        // Kolor gracza: true to biale, false to czarne
        bool isWhite;

        // Funkcja do pobierania wspolrzednych od użytkownika
        Piece* getPieceFromUser(const Board& board);

        // Funkcja rysujaca plansze i wyswietlajaca dostepne ruchy
        void displayBoard(const Board& board, std::vector<move_ptr_t> moce);

    public:
        // Konstruktor
        HumanPlayer(bool isWhite);

        // Nadpisana funkcja z klasy Player do pobierania ruchu w kazdej turze
        virtual void getMove(Board& board) override;
};

#endif