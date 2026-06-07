#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <vector>
#include <array>
#include <memory>

class Move;

// Wspolrzedne jako dwuelementowy array [X, Y], zeby kod byl czystszy
typedef std::array<int, 2> coords_t;

// Inteligentne wskazniki do ruchow, zeby nie bawic sie w reczne delete
typedef std::vector<std::shared_ptr<Move>> moves_t;
typedef std::shared_ptr<Move> move_ptr_t;

#endif