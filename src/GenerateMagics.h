#ifndef SRC_GENERATEMAGICS_H_
#define SRC_GENERATEMAGICS_H_

#include <random>

namespace Magics {
/**
 * Creates a list of occupancy masks for rooks for each square. The mask
 * consists of all squares that can be moved to by the piece, excluding
 * the most distant square it could move to in each direction.
 *
 * For example, the mask for a rook on c1 is:
 * 8 . . . . . . . .
 * 7 . . X . . . . .
 * 6 . . X . . . . .
 * 5 . . X . . . . .
 * 4 . . X . . . . .
 * 3 . . X . . . . .
 * 2 . . X . . . . .
 * 1 . X . X X X X .
 *   a b c d e f g h
 *
 * @return An ordered list of all occupancy masks for rooks on all squares,
 * beginning at square 0 (A1).
 */
std::vector<U64> generateRookOccupancyMasks();

/**
 * Creates a list of occupancy masks for bishops for each square. The mask
 * consists of all squares that can be moved to by the piece, excluding
 * the most distant square it could move to in each direction.
 *
 * For example, the mask for a bishop on d4 is:
 * 8 . . . . . . . .
 * 7 . . . . . . X .
 * 6 . X . . . X . .
 * 5 . . X . X . . .
 * 4 . . . . . . . .
 * 3 . . X . X . . .
 * 2 . X . . . X . .
 * 1 . . . . . . . .
 *   a b c d e f g h
 *
 * @return An ordered list of all occupancy masks for bishops on all squares,
 * beginning at square 0 (A1).
 */
std::vector<U64> generateBishopOccupancyMasks();

/**
 * Generates all possible occupancy mask variations for given occupancy masks.
 *
 * @param masks Occupancy masks for some piece for each square on the board.
 * @return All occupancy mask variations for each of the given occupancy masks.
 * The index of each set of variations corresponds to the index of mask that
 * they are variations of.
 */
std::vector<std::vector<U64> > generateOccupancyVariations(std::vector<U64> masks);

/**
 * Generates all bitwise OR combinations of a list of given bitmasks.
 *
 * @param masks The bitmasks to make combinations of.
 * @param acc The accumulator for storing which bitmasks should be OR'd
 * together. Each index corresponds to the mask with the same index. A mask will
 * be included as part of the combination iff its corresponding value is true.
 * @param variations The list that all generated combinations will be added to.
 * @param bitIndex The starting index in the list of bitmasks from which all
 * combinations will be generated. Indices less than this value in the
 * accumulator will not be changed.
 */
void generateVariations(std::vector<U64>& masks, bool acc[], std::vector<U64>& variations, int bitIndex=0);

/**
 * Generates the attack set of all rook occupancy mask variations. The attack
 * set of an occupancy mask is the bitboard of the first blocker or edge
 * encountered in each direction that the rook can move.
 *
 * For example, the attack set for an occupancy mask for a rook on c1 is:
 *  (Occupancy Mask)         (Attack set)
 * 8 . . . . . . . .      8 . . . . . . . .
 * 7 . . X . . . . .      7 . . . . . . . .
 * 6 . . . . . . . .      6 . . . . . . . .
 * 5 . . X . . . . .      5 . . X . . . . .
 * 4 . . . . . . . .      4 . . . . . . . .
 * 3 . . . . . . . .      3 . . . . . . . .
 * 2 . . . . . . . .      2 . . . . . . . .
 * 1 . X . X X . X .      1 . X . X . . . .
 *   a b c d e f g h        a b c d e f g h
 *
 * @param variations The rook occupancy mask variations for each square.
 * @return The attack set for each of the given occupancy mask variations. The
 * index of each attack set corresponds to the index of the variation it is for
 * in the given variations list.
 */
std::vector<std::vector<U64> > generateRookAttackSets(const std::vector<std::vector<U64> >& variations);

/**
 * Generates the attack set of all bishop occupancy mask variations. The attack
 * set of an occupancy mask is the bitboard of the first blocker or edge
 * encountered in each direction that the bishop can move.
 *
 * For example, the attack set for an occupancy mask for a bishop on d4 is:
 *  (Occupancy Mask)         (Attack set)
 * 8 . . . . . . . .      8 . . . . . . . .
 * 7 . . . . . . X .      7 . . . . . . . .
 * 6 . X . . . X . .      6 . . . . . X . .
 * 5 . . X . . . . .      5 . . X . . . . .
 * 4 . . . . . . . .      4 . . . . . . . .
 * 3 . . . . X . . .      3 . . . . X . . .
 * 2 . . . . . X . .      2 . . . . . . . .
 * 1 . . . . . . . .      1 X . . . . . . .
 *   a b c d e f g h        a b c d e f g h
 *
 * @param variations The bishop occupancy mask variations for each square.
 * @return The attack set for each of the given occupancy mask variations. The
 * index of each attack set corresponds to the index of the variation it is for
 * in the given variations list.
 */
std::vector<std::vector<U64> > generateBishopAttackSets(const std::vector<std::vector<U64> >& variations);

std::vector<U64> generateMagics(std::vector<U64> masks, std::vector<std::vector<U64> > variations, std::vector<std::vector<U64> > attackSets);
}

#endif /* SRC_GENERATEMAGICS_H_ */
