# Nazwa pliku koncowego
TARGET = projekt-warcaby.exe

# Kompilator i flagi standardu
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Flagi dla linkera (w64devkit/windows)
LDFLAGS = -Wl,-subsystem,console -static-libgcc -static-libstdc++

# Pliki obiektowe do utworzenia
OBJS = main.o AIPlayer.o Board.o HumanPlayer.o Move.o Piece.o

# Domyslna regula uruchamiana przez 'make'
all: $(TARGET)

# Linkowanie wszystkiego w plik .exe
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Kompilacja poszczegolnych plikow zrodlowych do .o
main.o: main.cpp Board.h Player.h HumanPlayer.h AIPlayer.h Typedefs.h
	$(CXX) $(CXXFLAGS) -c main.cpp

AIPlayer.o: AIPlayer.cpp AIPlayer.h Player.h Board.h Move.h Piece.h Typedefs.h
	$(CXX) $(CXXFLAGS) -c AIPlayer.cpp

Board.o: Board.cpp Board.h Piece.h Move.h Typedefs.h
	$(CXX) $(CXXFLAGS) -c Board.cpp

HumanPlayer.o: HumanPlayer.cpp HumanPlayer.h Player.h Board.h Move.h Piece.h Typedefs.h
	$(CXX) $(CXXFLAGS) -c HumanPlayer.cpp

Move.o: Move.cpp Move.h Board.h Piece.h Typedefs.h
	$(CXX) $(CXXFLAGS) -c Move.cpp

Piece.o: Piece.cpp Piece.h Board.h Move.h Typedefs.h
	$(CXX) $(CXXFLAGS) -c Piece.cpp

# Czyszczenie kompilacji (wywolanie: make clean)
clean:
	rm -f $(OBJS) $(TARGET)