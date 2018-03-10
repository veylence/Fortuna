#include "Bitboard.h"

std::string Bitboard::toString(U64 bitboard) {
  std::string s = "";

  // Process all ranks
  for (int rank = 7; rank >= 0; rank--) {
    // Add rank number
    s += (char) ('1' + rank);
    // Add each square in this rank
    for (int file = 0; file < 8; file++) {
      U64 square = 1ULL << (rank * 8 + file);

      s += ' ';
      if (bitboard & square) {
        s += 'X';
      } else {
        s += '.';
      }
    }
    s += '\n';
  }
  // Add file letters
  s += "  ";
  for (int i = 0; i < 8; i++) {
    s += (char) ('a' + i);
    s += ' ';
  }

  return s;
}

U64 Bitboard::lsb(U64 bitboard) {
  return bitboard & -bitboard;
}

U64 Bitboard::popLsb(U64& bitboard) {
  U64 lsb = Bitboard::lsb(bitboard);
  bitboard &= bitboard - 1;
  return lsb;
}
