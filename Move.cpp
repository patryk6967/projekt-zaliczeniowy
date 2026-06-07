#include "Move.h"
#include "Board.h"
#include "Piece.h"

// Zwraca tablice ze wspolrzednymi startowymi ruchu (X1, Y1)
coords_t Move::getStartingPosition() const
{
    coords_t pozycja;
    pozycja[0] = this->x1;
    pozycja[1] = this->y1;
    return pozycja;
}

// Zwraca tablice ze wspolrzednymi docelowymi ruchu (X2, Y2)
coords_t Move::getEndingPosition() const
{
    coords_t pozycja;
    pozycja[0] = this->x2;
    pozycja[1] = this->y2;
    return pozycja;
}

// Szuka i zwraca liste pionkow, ktore bije ten ruch
std::vector<Piece*> Move::getJumpedPieces(const Board& board) const
{
    std::vector<Piece*> zbitePionki;

    // Jesli to byl skok/bicie, szukamy pionka stojacego dokladnie posrodku
    if (this->isJump)
    {
        int srodekX = (this->x1 + this->x2) / 2;
        int srodekY = (this->y1 + this->y2) / 2;
        Piece* pionek = board.getValueAt(srodekX, srodekY);
        if (pionek != nullptr)
        {
            zbitePionki.push_back(pionek);
        }
    }

    // Jesli to bylo bicie wielokrotne, pobieramy rekurencyjnie reszte zbitych pionkow
    if (this->precedingMove != nullptr)
    {
        std::vector<Piece*> poprzednieZbite = this->precedingMove->getJumpedPieces(board);
        zbitePionki.insert(zbitePionki.end(), poprzednieZbite.begin(), poprzednieZbite.end());
    }

    return zbitePionki;
}