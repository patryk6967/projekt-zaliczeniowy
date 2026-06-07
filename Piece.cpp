#include "Piece.h"
#include "Board.h"
#include "Move.h"

// Konstruktor nowego pionka - ustawiamy pozycje, kolor i ze na start nie jest damka
Piece::Piece(int x, int y, bool isWhite) : x(x), y(y), isWhite(isWhite), isKing(false) {}

// Pobieranie aktualnych wspolrzednych pionka w tablicy
coords_t Piece::getCoordinates() const
{
    coords_t coords;
    coords[0] = this->x;
    coords[1] = this->y;
    return coords;
}

// Sprawdzenie czy pionek jest bialy
bool Piece::isWhitePiece() const
{
    return this->isWhite;
}

// Sprawdzenie czy pionek to damka
bool Piece::isKingPiece() const
{
    return this->isKing;
}

// Zmiana pozycji pionka na planszy
void Piece::moveTo(int newX, int newY)
{
    this->x = newX;
    this->y = newY;
}

// Sprawdzanie czy pionek doszedl do konca planszy i nalezy go zmienic w damke
void Piece::checkIfShouldBeKing(const Board& board)
{
    if (this->isWhite && this->y == board.SIZE - 1)
    {
        this->isKing = true;
    }
    else if (!this->isWhite && this->y == 0)
    {
        this->isKing = true;
    }
}

// Szukanie wszystkich ruchow jakie moze zrobic ten pionek
std::vector<move_ptr_t> Piece::getPossibleMoves(const Board& board) const
{
    std::vector<move_ptr_t> moves;

    // Ustalamy kierunki: zwykle pionki ida tylko przed siebie, damki moga tez w tyl
    std::vector<int> yDirections;
    if (this->isKing)
    {
        yDirections = {1, -1};
    }
    else
    {
        yDirections = { this->isWhite ? 1 : -1 };
    }

    std::vector<int> xDirections = {1, -1};

    // Glowna petla sprawdzajaca skosy pod katem wolnych pol i bic
    for (int dy : yDirections)
    {
        for (int dx : xDirections)
        {
            int targetX = this->x + dx;
            int targetY = this->y + dy;

            // Omijamy pola, ktore wychodza poza plansze
            if (board.isOverEdge(targetX, targetY)) continue;

            Piece* targetPiece = board.getValueAt(targetX, targetY);

            // Opcja 1: Zwykly krok na wolne pole obok
            if (targetPiece == nullptr)
            {
                moves.push_back(std::make_shared<Move>(this->x, this->y, targetX, targetY, false));
            }
            // Opcja 2: Sprawdzamy czy mozna przeskoczyc (zbic) pionek wroga
            else if (targetPiece->isWhitePiece() != this->isWhite)
            {
                int jumpX = targetX + dx;
                int jumpY = targetY + dy;

                // Jesli pole za wrogiem jest wolne i na planszy, to mamy bicie
                if (!board.isOverEdge(jumpX, jumpY) && board.getValueAt(jumpX, jumpY) == nullptr)
                {
                    moves.push_back(std::make_shared<Move>(this->x, this->y, jumpX, jumpY, true));
                }
            }
        }
    }

    return moves;
}