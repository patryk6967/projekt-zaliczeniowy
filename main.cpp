#include "Board.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "Piece.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

// Sprawdzanie czy gra sie skonczyla (brak pionkow albo brak ruchu)
bool endGame(const Board& board)
{
    int liczbaRuchomychBialych = 0;
    int liczbaRuchomychCzarnych = 0;

    // Przechodzimy po calej planszy i liczymy pionki, ktore moga wykonac jakis ruch
    for (int pozycja = 0; pozycja < Board::SIZE * Board::SIZE; pozycja++)
    {
        Piece* pionekTutaj = board.getValueAt(pozycja);

        if (pionekTutaj != nullptr)
        {
            if (!pionekTutaj->getPossibleMoves(board).empty())
            {
                if (pionekTutaj->isWhitePiece())
                {
                    liczbaRuchomychBialych++;
                }
                else
                {
                    liczbaRuchomychCzarnych++;
                }
            }
        }
    }

    // Jesli ktoras strona nie moze zrobic zadnego ruchu, konczymy gre
    if (liczbaRuchomychBialych == 0 || liczbaRuchomychCzarnych == 0)
    {
        return true;
    }

    return false;
}

// Start programu
int main()
{
    // Inicjalizacja losowania dla bota
    srand(static_cast<unsigned int>(time(nullptr)));

    std::cout << "=================================\n";
    std::cout << "===    WITAJ W GRZE WARCABY   ===\n";
    std::cout << "=================================\n\n";

    std::cout << "Wybierz tryb gry:\n";
    std::cout << "1. Gra z komputerem (AI)\n";
    std::cout << "2. Gra z drugim graczem (Lokalnie)\n";
    std::cout << "Twoj wybor (1 lub 2): ";
    
    int wyborTrybu = 0;
    std::cin >> wyborTrybu;

    // Zabezpieczenie przed wpisaniem czegos innego niz 1 lub 2
    while (wyborTrybu != 1 && wyborTrybu != 2)
    {
        std::cout << "Nieprawidlowy wybor! Wpisz 1 lub 2: ";
        std::cin >> wyborTrybu;
    }

    // Tworzymy plansze gry
    Board board;

    // Gracz 1 to zawsze czlowiek (Biale)
    Player* gracz1 = new HumanPlayer(true);
    
    // Gracz 2 dostaje obiekt w zaleznosci od tego, co wybralismy w menu
    Player* gracz2 = nullptr;

    if (wyborTrybu == 1)
    {
        std::cout << "\nWybrano gre z komputerem. Powodzenia!\n";
        gracz2 = new AIPlayer(false); // Komputer gra jako czarne
    }
    else
    {
        std::cout << "\nWybrano gre dla dwoch graczy. Zaczynaja Biale!\n";
        gracz2 = new HumanPlayer(false); // Drugi czlowiek gra jako czarne
    }

    bool turaBialych = true;

    // Glowna petla rozgrywki
    while (!endGame(board))
    {
        if (turaBialych)
        {
            gracz1->getMove(board);
        }
        else
        {
            if (wyborTrybu == 1)
            {
                std::cout << "\nRuch wykonuje komputer..." << std::endl;
            }
            gracz2->getMove(board);
        }
        
        // Zmiana gracza po wykonaniu ruchu
        turaBialych = !turaBialych;
    }

    std::cout << "\n=== KONIEC GRY ===" << std::endl;

    // Obowiazkowe sprzatanie pamieci po "new"
    delete gracz1;
    delete gracz2;

    return 0;
}