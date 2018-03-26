#ifndef TYPES_H_
#define TYPES_H_

#include<cstdint>

// Unsigned 64-bit number
typedef uint64_t U64;

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
// Files of the board
enum File : int {
  FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H,
  FILE_NONE,
  FILE_NUM = 8
};
// Ranks of the board
enum Rank : int {
  RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8,
  RANK_NONE,
  RANK_NUM = 8
};
// File bitboards
enum FileBB : U64 {
  FILE_A_BB = 0x0101010101010101L,
  FILE_B_BB = 0x0202020202020202L,
  FILE_C_BB = 0x0404040404040404L,
  FILE_D_BB = 0x0808080808080808L,
  FILE_E_BB = 0x1010101010101010L,
  FILE_F_BB = 0x2020202020202020L,
  FILE_G_BB = 0x4040404040404040L,
  FILE_H_BB = 0x8080808080808080L
};
// Rank bitboards
enum RankBB : U64 {
  RANK_1_BB = 0x00000000000000FFL,
  RANK_2_BB = 0x000000000000FF00L,
  RANK_3_BB = 0x0000000000FF0000L,
  RANK_4_BB = 0x00000000FF000000L,
  RANK_5_BB = 0x000000FF00000000L,
  RANK_6_BB = 0x0000FF0000000000L,
  RANK_7_BB = 0x00FF000000000000L,
  RANK_8_BB = 0xFF00000000000000L
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

// Player castling rights
enum CastlingRight : int {
  NO_CASTLING,
  W_KINGSIDE  = 1 << 0,
  W_QUEENSIDE = 1 << 1,
  B_KINGSIDE  = 1 << 2,
  B_QUEENSIDE = 1 << 3,
  ANY_CASTLING = W_KINGSIDE | W_QUEENSIDE | B_KINGSIDE | B_QUEENSIDE,
  CASTLING_NUM = 16 // Number of combinations of castling rights
};

// A move is represented by a 16-bit integer.
// Bits 0-5:   Destination square (0 to 63)
// Bits 6-11:  Origin square (0 to 63)
// Bits 12-13: Promotion piece type (Knight, Bishop, Rook, Queen)
// Bits 14-15: Special flags (1 = promotion, 2 = en passant, 3 = castling)
enum Move : int {
  MOVE_NONE
};
const int ORIGIN_MASK    = 0b0000111111000000;
const int PROMOTION_MASK = 0b0011000000000000;
const int SPECIAL_MASK   = 0b1100000000000000;
const int ORIGIN_SHIFT    = 6;
const int PROMOTION_SHIFT = 12;
const int SPECIAL_SHIFT   = 14;

/**
 * Scored move.
 */
struct MoveEntry {
  Move* move;
  int score;
};

/**
 * Shifts a given bitboard in a direction.
 *
 * @param bb The bitboard to shift.
 * @param d The direction to shift the bitboard in.
 * @return The given bitboard, with all bits shifted in the given direction.
 */
template<Direction D>
constexpr U64 shift(U64 bb) {
  return D == NW ? bb << NW : D == N  ? bb << N  : D == NE ? bb << NE :
         D == E  ? bb << E  : D == SE ? bb >> NW : D == S  ? bb >> N  :
         D == SW ? bb >> NE : D == W  ? bb >> E  : 0;
}

/**
 * Returns the file of the given square.
 *
 * @param s The square to get the file of.
 * @return The file of the given square.
 */
constexpr File fileOf(Square s) {
  // The file of a square is: square % 8, which will be the lowest 3 bits
  return File(s & 0b111);
}

/**
 * Returns the rank of the given square.
 *
 * @param s The square to get the rank of.
 * @return The rank of the given square.
 */
constexpr Rank rankOf(Square s) {
  // The rank of a square is: square / 8. Here this is done via division by
  // right shift.
  return Rank(s >> 3);
}

#endif /* TYPES_H_ */
