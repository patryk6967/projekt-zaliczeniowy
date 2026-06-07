#ifndef BOARD_H
#define BOARD_H

#include <array>
#include "Typedefs.h"

class Piece;
class Move;
    
// Klasa do obslugi i przechowywania stanu planszy
class Board
{
    public:
        // Rozmiar planszy (stała, zeby nie bawic sie w dynamiczne tablice)
        const static int SIZE = 8;

        // Konstruktory i destruktor
        Board();
        Board(const Board& staraPlansza);
        ~Board();
   
        // Wykonanie ruchu na planszy
        void applyMoveToBoard(const move_ptr_t move, Piece* pionek);
    
        // Pobranie pionka ze wspolrzednych X i Y
        Piece* getValueAt(int x, int y) const { return this->boardArray[y][x]; }
    
        // Pobranie pionka po indeksie (0-63)
        Piece* getValueAt(int pozycja) const;
    
        // Zamiana wspolrzednych na jeden numer pola
        int getPosFromCoords(int x, int y) const;
    
        // Sprawdzenie czy pole jest czarne (pole gry)
        bool isCheckerboardSpace(int x, int y) const;
        
        // Sprawdzanie czy ruch nie wychodzi poza plansze
        bool isOverEdge(int x, int y) const;
        bool isOverEdge(int pozycja) const;
        
    private:
        // Tablica dwuwymiarowa przechowujaca wskazniki na pionki
        Piece* boardArray[SIZE][SIZE];
    
        // Prywatne funkcje pomocnicze do ustawiania wartosci i przeliczania pozycji
        void setValueAt(int x, int y, Piece* pionek) 
        { this->boardArray[y][x] = pionek; }
        
        void setValueAt(int pozycja, Piece* pionek);
        
        coords_t getCoordsFromPos(int pozycja) const;
};

#endif