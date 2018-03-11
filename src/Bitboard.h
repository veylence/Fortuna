#ifndef BITBOARD_H_
#define BITBOARD_H_

#include <cassert>
#include <string>

#include "Types.h"

namespace Bitboard {

// 64-bit de Bruijn sequence used to determine index in a bitscan
const U64 DE_BRUIJN_64 = 0x03f79d71b4cb0a89ULL;
// Lookup table for bitscan indices
const int BIT_SCAN_INDEX[Square::NUM] = {
  0,  1,  48,  2, 57, 49, 28,  3,
  61, 58, 50, 42, 38, 29, 17,  4,
  62, 55, 59, 36, 53, 51, 43, 22,
  45, 39, 33, 30, 24, 18, 12,  5,
  63, 47, 56, 27, 60, 41, 37, 16,
  54, 35, 52, 21, 44, 32, 23, 11,
  46, 26, 40, 15, 34, 20, 31, 10,
  25, 14, 19,  9, 13,  8,  7,  6
};

/**
 * Creates a string representation of a little endian rank-file (LERF)
 * bitboard as an 8x8 grid with ranks and files labeled. 0 bits appear as
 * '.' and 1 bits appear as 'X'.
 *
 * For example, toString(9) would return:
 * 8 . . . . . . . .
 * 7 . . . . . . . .
 * 6 . . . . . . . .
 * 5 . . . . . . . .
 * 4 . . . . . . . .
 * 3 . . . . . . . .
 * 2 . . . . . . . .
 * 1 X . . X . . . .
 *   a b c d e f g h
 *
 * @param bitboard The bitboard to create a string representation for.
 * @return An 8x8 grid representation of the given bitboard.
 */
std::string toString(U64 bitboard);

/**
 * Returns a bitboard containing just the least significant 1 bit (LS1B)
 * of a given bitboard.
 *
 * @param bitboard The bitboard to get the LS1B of.
 * @return A bitboard of just the LS1B of the given bitboard.
 */
U64 lsb(U64 bitboard);

/**
 * Removes the least significant 1 bit (LS1B) of a given bitboard and
 * returns it as its own bitboard.
 *
 * @param bitboard The bitboard to find and remove the LS1B of.
 * @return A bitboard of just the LS1B of the given bitboard.
 */
U64 popLsb(U64& bitboard);

/**
 * Counts the number of 1 bits in a bitboard (i.e. computes the Hamming
 * weight).
 *
 * This implementation should be preferred when the bitboard is sparse.
 *
 * @param bitboard The bitboard to count the number of 1 bits of.
 * @return The number of 1 bits in the bitboard.
 */
int sparseCount(U64 bitboard);

/**
 * Bitscan forward to determine the index of the least significant 1 bit in a
 * given bitboard.
 *
 * @author Martin Läuter (1997)
 *         Charles E. Leiserson
 *         Harald Prokop
 *         Keith H. Randall
 * "Using de Bruijn Sequences to Index a 1 in a Computer Word"
 *
 * @param bitboard The bitboard to determine the index of the LS1B for. Must
 * not be 0.
 * @return The index of the LS1B in the given bitboard.
 */
int bsfIndex(U64 bitboard);
}

#endif /* BITBOARD_H_ */
