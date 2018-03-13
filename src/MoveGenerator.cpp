#include "MoveGenerator.h"

U64* MoveGenerator::ROOK_MOVES[Square::NUM];
U64* MoveGenerator::BISHOP_MOVES[Square::NUM];

void MoveGenerator::init() {
  // Initialize rook move database
  std::vector<U64> rookOccupancyMasks = Magics::generateRookOccupancyMasks();
  std::vector<std::vector<U64> > rookOccupancyMaskVariations = Magics::generateOccupancyVariations(rookOccupancyMasks);
  std::vector<std::vector<U64> > rookAttackSets = Magics::generateRookAttackSets(rookOccupancyMaskVariations);

  for(int square = 0; square < Square::NUM; square++) {
    free(ROOK_MOVES[square]);
    ROOK_MOVES[square] = new U64[rookOccupancyMaskVariations[square].size()];

    for(int i = 0; i < rookOccupancyMaskVariations[square].size(); i++) {
      U64 variation = rookOccupancyMaskVariations[square][i];
      int magicIndex = (variation * MAGIC_NUMBERS_ROOKS[square]) >> MAGIC_NUMBER_SHIFTS_ROOK[square];

      ROOK_MOVES[square][magicIndex] = rookAttackSets[square][i];
    }
  }

  // Initialize bishop move database
  std::vector<U64> bishopOccupancyMasks = Magics::generateBishopOccupancyMasks();
  std::vector<std::vector<U64> > bishopOccupancyMaskVariations = Magics::generateOccupancyVariations(bishopOccupancyMasks);
  std::vector<std::vector<U64> > bishopAttackSets = Magics::generateBishopAttackSets(bishopOccupancyMaskVariations);

  for(int square = 0; square < Square::NUM; square++) {
    free(BISHOP_MOVES[square]);
    BISHOP_MOVES[square] = new U64[bishopOccupancyMaskVariations[square].size()];

    for(int i = 0; i < bishopOccupancyMaskVariations[square].size(); i++) {
      U64 variation = bishopOccupancyMaskVariations[square][i];
      int magicIndex = (variation * MAGIC_NUMBERS_BISHOPS[square]) >> MAGIC_NUMBER_SHIFTS_BISHOP[square];

      BISHOP_MOVES[square][magicIndex] = bishopAttackSets[square][i];
    }
  }
}

