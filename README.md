Warcaby (C++)
CEL PROJEKTU
Stworzenie gry w warcaby przeznaczonej dla 2 graczy oraz dla 1 gracza (rozgrywka przeciwko sztucznej inteligencji - AI).

ZALEŻNOŚCI (WYMAGANIA)
Kompilator g++, biblioteka standardowa C/C++.

JAK URUCHOMIĆ PROJEKT
Uruchom polecenie make w terminalu, aby skompilować projekt (opcjonalnie możesz wcześniej wykonać make clean). Następnie uruchom główny program za pomocą komendy ./checkers.

PODSUMOWANIE KLAS
HumanPlayer
Odpowiada za interakcję z graczem człowieczym w celu pobrania jego ruchu i zastosowania go na planszy.

Uwaga: Założenia projektu zostały w tym miejscu zmienione – ruchy są teraz identyfikowane poprzez wyświetlenie użytkownikowi listy legalnych opcji, z której dokonuje on wyboru.

AIPlayer
Odpowiada za wykorzystanie algorytmów sztucznej inteligencji do wyznaczenia efektywnego ruchu i zastosowania go na planszy.

Board
Przechowuje stan planszy oraz pionków i umożliwia manipulowanie nimi.

Piece
Odpowiada za przechowywanie danych powiązanych z konkretnym pionkiem oraz określanie jego właściwości (takich jak np. dostępne ruchy).

Move
Przechowuje dane związane z ruchem pionka oraz udostępnia metody do wyznaczania jego dalszych właściwości (np. pobieranie zbitych pionków).

Typedef.h
Zawiera kilka definicji typów danych (aliasów), które są niezbędne w różnych aspektach działania programu.

Podsumowanie pozostałych klas:
Player (Klasa abstrakcyjna)
Odpowiada za zarysowanie wspólnych metod dla klas HumanPlayer i AIPlayer, dzięki czemu mogą być one używane w kodzie zamiennie (polimorfizm).