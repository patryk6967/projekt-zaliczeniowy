#include "AIPlayer.h"
#include "Board.h"
#include "Move.h"
#include "Piece.h"
#include "Typedefs.h"

#include <iostream>
#include <vector>
#include <cstdlib>

// Konstruktor dla bota, ustawiamy kolor pionkow
AIPlayer::AIPlayer(bool isWhite) : Player() 
{
    this->isWhite = isWhite;
}

// Glowna funkcja bota - szuka i robi losowy ruch
void AIPlayer::getMove(Board& board)
{
    std::vector<move_ptr_t> wszystkieRuchy;
    std::vector<Piece*> mojePionki;

    // Przechodzimy po calej planszy i szukamy pionkow bota
    for (int pozycja = 0; pozycja < Board::SIZE * Board::SIZE; pozycja++)
    {
        Piece* pionek = board.getValueAt(pozycja);

        // Sprawdzamy czy pole nie jest puste i czy pionek nalezy do nas
        if (pionek != nullptr && pionek->isWhitePiece() == this->isWhite)
        {
            std::vector<move_ptr_t> mozliweRuchy = pionek->getPossibleMoves(board);
            
            // Jesli ten pionek ma jakies ruchy, to zapisujemy go i jego ruchy
            if (!mozliweRuchy.empty())
            {
                mojePionki.push_back(pionek);
                wszystkieRuchy.insert(wszystkieRuchy.end(), mozliweRuchy.begin(), mozliweRuchy.end());
            }
        }
    }

    // Losowanie ruchu, jesli jest z czego wybierac
    if (!wszystkieRuchy.empty())
    {
        int losowyIndeks = rand() % wszystkieRuchy.size();
        move_ptr_t wybranyRuch = wszystkieRuchy[losowyIndeks];
        
        // Szukamy, ktory pionek mial ten konkretny wylosowany ruch
        for (Piece* p : mojePionki)
        {
            std::vector<move_ptr_t> ruchyPionka = p->getPossibleMoves(board);
            for (auto& r : ruchyPionka)
            {
                // Sprawdzanie wspolrzednych startowych i docelowych
                if (r->x1 == wybranyRuch->x1 && r->y1 == wybranyRuch->y1 &&
                    r->x2 == wybranyRuch->x2 && r->y2 == wybranyRuch->y2)
                {
                    // Ruszamy pionkiem na planszy i konczymy ture bota
                    board.applyMoveToBoard(wybranyRuch, p);
                    return;
                }
            }
        }
    }
}