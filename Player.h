#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Board;

// Abstrakcyjna klasa bazowa dla gracza (czlowieka i bota)
class Player
{
    protected:
        std::string name; // Nick/Nazwa gracza
        bool isWhite;     // Kolor pionkow: true = biale, false = czarne

    public:
        // Konstruktory
        Player() : name("Gracz"), isWhite(true) {}
        Player(std::string name, bool isWhite) : name(name), isWhite(isWhite) {}

        // Wirtualny destruktor - wazny, zeby poprawnie czyscic pamiec klas pochodnych
        virtual ~Player() = default;

        // Czysto wirtualna funkcja do nadpisania (pobieranie ruchu w turze)
        virtual void getMove(Board& board) = 0;

        // Gettery do pobierania nazwy i koloru
        std::string getName() const { return name; }
        bool isWhitePlayer() const { return isWhite; }
};

#endif