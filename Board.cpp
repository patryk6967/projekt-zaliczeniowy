
#include "Board.h"
#include "HumanPlayer.h"
#include "Piece.h"
#include "Move.h"
#include "Typedefs.h"

// Tworzenie nowej planszy ze startowym ustawieniem pionkow
Board::Board()
{
    // Rezerwujemy pamiec na pionki przez "new", zeby dzialac na wskaznikach
    // i nie kopiowac calych obiektów przy kazdym ruchu. Trzeba pamietac o delete w destruktorze!
    for (int y = 0; y < SIZE; y++)
    {
        for (int x = 0; x < SIZE; x++)
        {
            // Biale pionki lądują na pierwszych 3 wierszach od gory
            if (y < 3 && isCheckerboardSpace(x, y))
            {
                setValueAt(x, y, new Piece(x, y, true));
            }
            // Czarne pionki lądują na ostatnich 3 wierszach na dole
            else if (y >= SIZE - 3 && isCheckerboardSpace(x, y))
            {
                setValueAt(x, y, new Piece(x, y, false));
            }
            // Reszta pol musi byc pusta, czyli dajemy nullptr
            else
            {
                setValueAt(x, y, nullptr);
            }
        }
    }
}

// Konstruktor kopiujacy plansze
Board::Board(const Board& staraPlansza)
{
    for (int pozycja = 0; pozycja < SIZE*SIZE; pozycja++)
    {
        setValueAt(pozycja, staraPlansza.getValueAt(pozycja));  
    }
}

// Destruktor - czyscimy pamiec po pionkach, zeby nie bylo wyciekow
Board::~Board()
{
    for (int pozycja = 0; pozycja < SIZE*SIZE; pozycja++)
    {
        delete getValueAt(pozycja);
        setValueAt(pozycja, nullptr);  
    }
}
    
// Wykonanie wybranego ruchu na planszy
void Board::applyMoveToBoard(const move_ptr_t move, Piece* pionek)
{
    coords_t pozycjaStartowa = pionek->getCoordinates();
    coords_t pozycjaKoncowa = move->getEndingPosition();
    
    // Pobieramy liste pionkow, ktore zostaly przeskoczone i je zbijamy
    std::vector<Piece*> zbitePionki = move->getJumpedPieces(*this);
    if (!zbitePionki.empty())
    {
        for (unsigned int i = 0; i < zbitePionki.size(); i++)
        {
            if (zbitePionki[i] != nullptr)
            {
                // Wywalamy zbity pionek z planszy (ustawiamy pole na puste)
                setValueAt(zbitePionki[i]->getCoordinates()[0], 
                           zbitePionki[i]->getCoordinates()[1], nullptr);
            }
        }
    }
        
    // Czyscimy stare miejsce pionka i zmieniamy jego wewnetrzne wspolrzedne
    setValueAt(pozycjaStartowa[0], pozycjaStartowa[1], nullptr);
    pionek->moveTo(pozycjaKoncowa[0], pozycjaKoncowa[1]);
    
    // Sprawdzamy, czy po tym ruchu pionek zmienia sie w damke
    pionek->checkIfShouldBeKing(*this);
    
    // Ustawiamy pionek na nowym miejscu na planszy
    setValueAt(pozycjaKoncowa[0], pozycjaKoncowa[1], pionek);
}
    
// Wrzucenie pionka na plansze przy uzyciu indeksu jednowymiarowego
void Board::setValueAt(int pozycja, Piece* pionek)
{
    coords_t koordynaty = getCoordsFromPos(pozycja); 
    setValueAt(koordynaty[0], koordynaty[1], pionek);
}

// Pobranie pionka przy uzyciu indeksu jednowymiarowego
Piece* Board::getValueAt(int pozycja) const
{
    coords_t koordynaty = getCoordsFromPos(pozycja); 
    return getValueAt(koordynaty[0], koordynaty[1]); 
}
    
// Przeliczenie numeru pola (0-63) na standardowe wspolrzedne X i Y
coords_t Board::getCoordsFromPos(int pozycja) const
{
    coords_t koordynaty;
    koordynaty[0] = pozycja % SIZE; // modulo daje kolumne
    koordynaty[1] = pozycja / SIZE; // dzielenie daje wiersz
    return koordynaty;
}
    
// Przeliczenie wspolrzednych X i Y na jeden numer pola od 0 do 63
int Board::getPosFromCoords(int x, int y) const
{
    return SIZE*y + x;
}
    
// Sprawdzanie czy dane pole jest czarne (tylko na nich gramy)
bool Board::isCheckerboardSpace(int x, int y) const
{
    return x % 2 == y % 2;
}
    
// Sprawdzanie czy wspolrzedne nie wyszly gdzies poza krawedz planszy
bool Board::isOverEdge(int x, int y) const
{
    return (x < 0 || x >= SIZE ||
            y < 0 || y >= SIZE);
}
    
// To samo sprawdzanie, ale dla indeksu jednowymiarowego
bool Board::isOverEdge(int pozycja) const
{
    coords_t koordynaty = getCoordsFromPos(pozycja); 
    return isOverEdge(koordynaty[0], koordynaty[1]); 
}