#ifndef TYPES_H_
#define TYPES_H_

// Unsigned 64-bit number
typedef unsigned long long U64;

// Dimension of the board, in squares
const int SIZE = 8;

// Squares on the board, using little endian rank-file (LERF) mapping.
// A1=0, H8=63
enum Square : int {
  A1, B1, C1, D1, E1, F1, G1, H1,
  A2, B2, C2, D2, E2, F2, G2, H2,
  A3, B3, C3, D3, E3, F3, G3, H3,
  A4, B4, C4, D4, E4, F4, G4, H4,
  A5, B5, C5, D5, E5, F5, G5, H5,
  A6, B6, C6, D6, E6, F6, G6, H6,
  A7, B7, C7, D7, E7, F7, G7, H7,
  A8, B8, C8, D8, E8, F8, G8, H8,
  SQ_NONE,
  SQ_NUM = 64
};

// Cardinal directions on the board from white's perspective, using LERF
// mapping.
enum Direction : int {
  N  = SIZE,
  E  = 1,
  S  = -SIZE,
  W  = -1,
  NE = N + E,
  SE = S + E,
  SW = S + W,
  NW = N + W
};

// Player colors
enum Color : int {
  WHITE, BLACK,
  COLOR_NUM
};

// Piece types and colors
enum Piece : int {
  W_PAWN, W_KNIGHT, W_BISHOP, W_ROOK, W_QUEEN, W_KING,
  B_PAWN, B_KNIGHT, B_BISHOP, B_ROOK, B_QUEEN, B_KING,
  PIECE_NONE,
  PIECE_NUM = 12
};

#endif /* TYPES_H_ */
