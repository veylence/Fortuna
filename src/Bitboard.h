#ifndef BITBOARD_H_
#define BITBOARD_H_

#include <string>

#include "Types.h"

namespace Bitboard {
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
 * Removes the least significant 1 bit (LS1b) of a given bitboard and
 * returns it as its own bitboard.
 *
 * @param bitboard The bitboard to find and remove the LS1B of.
 * @return A bitboard of just the LS1B of the given bitboard.
 */
U64 popLsb(U64& bitboard);
}

#endif /* BITBOARD_H_ */
