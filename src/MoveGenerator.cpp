#include "MoveGenerator.h"
#include "Bitboard.h"

U64* MoveGen::ROOK_MOVES[Square::SQ_NUM];
U64* MoveGen::BISHOP_MOVES[Square::SQ_NUM];

void MoveGen::init() {
  // Initialize rook move database
  std::vector<U64> rookOccupancyMasks = Magics::generateRookOccupancyMasks();
  std::vector<std::vector<U64> > rookOccupancyMaskVariations = Magics::generateOccupancyVariations(rookOccupancyMasks);
  std::vector<std::vector<U64> > rookAttackSets = Magics::generateRookAttackSets(rookOccupancyMaskVariations);

  for(int square = 0; square < Square::SQ_NUM; square++) {
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

  for(int square = 0; square < Square::SQ_NUM; square++) {
    free(BISHOP_MOVES[square]);
    BISHOP_MOVES[square] = new U64[bishopOccupancyMaskVariations[square].size()];

    for(int i = 0; i < bishopOccupancyMaskVariations[square].size(); i++) {
      U64 variation = bishopOccupancyMaskVariations[square][i];
      int magicIndex = (variation * MAGIC_NUMBERS_BISHOPS[square]) >> MAGIC_NUMBER_SHIFTS_BISHOP[square];

      BISHOP_MOVES[square][magicIndex] = bishopAttackSets[square][i];
    }
  }
}

U64 MoveGen::genKnightMovesBB(U64 piece, U64 myBoard) {
  int index = Bitboard::bsfIndex(piece);
  return KNIGHT_MOVES[index] & ~myBoard;
}

U64 MoveGen::genBishopMovesBB(U64 piece, U64 myBoard, U64 oppBoard) {
  int square = Bitboard::bsfIndex(piece);
  assert(BISHOP_MOVES[square] != nullptr);
  U64 occupancy = OCCUPANCY_MASKS_BISHOP[square] & (myBoard | oppBoard);
  int magicIndex = (occupancy * MAGIC_NUMBERS_BISHOPS[square]) >> MAGIC_NUMBER_SHIFTS_BISHOP[square];

  return BISHOP_MOVES[square][magicIndex] & ~myBoard;
}

U64 MoveGen::genRookMovesBB(U64 piece, U64 myBoard, U64 oppBoard) {
  int square = Bitboard::bsfIndex(piece);
  assert(ROOK_MOVES[square] != nullptr);
  U64 occupancy = OCCUPANCY_MASKS_ROOK[square] & (myBoard | oppBoard);
  int magicIndex = (occupancy * MAGIC_NUMBERS_ROOKS[square]) >> MAGIC_NUMBER_SHIFTS_ROOK[square];

  return ROOK_MOVES[square][magicIndex] & ~myBoard;
}

U64 MoveGen::genQueenMovesBB(U64 piece, U64 myBoard, U64 oppBoard) {
  return genBishopMovesBB(piece, myBoard, oppBoard) | genRookMovesBB(piece, myBoard, oppBoard);
}

U64 MoveGen::genKingMovesBB(U64 piece, U64 myBoard) {
  int index = Bitboard::bsfIndex(piece);
  return KING_MOVES[index] & ~myBoard;
}

