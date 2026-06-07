#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "Player.h"
#include "Typedefs.h"
#include <vector>

class Board;

// Klasa bota (komputera)
class AIPlayer : public Player
{
    private:
        // Kolor bota: true to biale, false to czarne
        bool isWhite;

    public:
        // Konstruktor
        AIPlayer(bool isWhite);

        // Nadpisana funkcja z klasy Player do robienia ruchu
        virtual void getMove(Board& board) override;
};

#endif