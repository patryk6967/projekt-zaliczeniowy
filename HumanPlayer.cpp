
#include "HumanPlayer.h"
#include "Board.h"
#include "Move.h"
#include "Piece.h"
#include "Typedefs.h"

#include <iostream>
#include <vector>
#include <string>

// Konstruktor gracza - przypisujemy kolor biale/czarne
HumanPlayer::HumanPlayer(bool isWhite) : Player() 
{
    this->isWhite = isWhite;
}

// Glowna funkcja tury gracza ludzkiego
void HumanPlayer::getMove(Board& board)
{
    std::vector<move_ptr_t> mozliweRuchy;
    Piece* wybranyPionek = nullptr;

    // Petla kreci sie poki gracz nie wybierze pionka, ktory moze gdzies ruszyc
    while (mozliweRuchy.empty())
    {
        wybranyPionek = getPieceFromUser(board);
        mozliweRuchy = wybranyPionek->getPossibleMoves(board);

        if (mozliweRuchy.empty())
        {
            std::cout << "Ten pionek nie ma dostepnych ruchow! Wybierz innego.\n";
        }
    }

    // Pokazujemy plansze z naniesionymi numerami ruchow
    displayBoard(board, mozliweRuchy);

    std::cout << "Wybierz ruch (wpisz numer od 0 do " << mozliweRuchy.size() - 1 << "): ";
    unsigned int wybor;
    std::cin >> wybor;

    // Zabezpieczenie przed wpisaniem zlego numeru ruchu
    while (wybor >= mozliweRuchy.size())
    {
        std::cout << "Nieprawidlowy numer. Wybierz ponownie: ";
        std::cin >> wybor;
    }

    // Przesuwamy pionek na planszy
    board.applyMoveToBoard(mozliweRuchy[wybor], wybranyPionek);
}

// Rysowanie planszy w konsoli razem z opcjami ruchow
void HumanPlayer::displayBoard(const Board& board, std::vector<move_ptr_t> moce)
{
    std::cout << "\n    0   1   2   3   4   5   6   7\n";
    std::cout << "  ---------------------------------\n";

    for (int y = 0; y < Board::SIZE; y++)
    {
        std::cout << y << " ";
        for (int x = 0; x < Board::SIZE; x++)
        {
            Piece* tenPionek = board.getValueAt(x, y);

            if (tenPionek != nullptr)
            {
                // Jesli jest pionek, to wyswietlamy b/B dla bialych i c/C dla czarnych
                if (tenPionek->isWhitePiece())
                {
                    std::cout << "| " << (tenPionek->isKingPiece() ? "B" : "b") << " ";
                }
                else
                {
                    std::cout << "| " << (tenPionek->isKingPiece() ? "C" : "c") << " ";
                }
            }
            else
            {
                // Jesli pole jest puste, sprawdzamy czy mozna tam skoczyc w tym ruchu
                bool czyPoleRuchu = false;
                int numerRuchu = -1;
                for (unsigned int i = 0; i < moce.size(); i++)
                {
                    if (moce[i]->x2 == x && moce[i]->y2 == y)
                    {
                        czyPoleRuchu = true;
                        numerRuchu = i;
                        break;
                    }
                }

                // Jesli to pole docelowe, drukujemy jego cyfre, w przeciwnym razie puste miejsce
                if (czyPoleRuchu)
                {
                    std::cout << "| " << numerRuchu << " ";
                }
                else
                {
                    std::cout << "|   ";
                }
            }
        }
        std::cout << "|\n  ---------------------------------\n";
    }
}

// Pobieranie od gracza wspolrzednych pionka i sprawdzanie bledow
Piece* HumanPlayer::getPieceFromUser(const Board& board)
{
    int x, y;
    Piece* pionekGracza = nullptr;

    while (pionekGracza == nullptr)
    {
        // Rysujemy czysta plansze bez numerow ruchow
        displayBoard(board, std::vector<move_ptr_t>());
        std::cout << "Twoja tura (" << (this->isWhite ? "Biale" : "Czarne") << ").\n";
        std::cout << "Podaj wspolrzedne pionka, ktorym chcesz sie ruszyc.\n";
        std::cout << "Podaj X (kolumna 0-7): ";
        std::cin >> x;
        std::cout << "Podaj Y (wiersz 0-7): ";
        std::cin >> y;

        // Walidacja: czy nie kliknelismy poza szachownice
        if (board.isOverEdge(x, y))
        {
            std::cout << "Wspolrzedne poza plansza! Sprobuj ponownie.\n";
            continue;
        }

        pionekGracza = board.getValueAt(x, y);

        // Walidacja: czy pole jest puste albo pionek nalezy do przeciwnika
        if (pionekGracza == nullptr)
        {
            std::cout << "Na tym polu nie ma zadnego pionka!\n";
        }
        else if (pionekGracza->isWhitePiece() != this->isWhite)
        {
            std::cout << "To nie jest Twoj pionek!\n";
            pionekGracza = nullptr;
        }
    }

    return pionekGracza;
}