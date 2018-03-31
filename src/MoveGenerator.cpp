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

std::vector<MoveEntry> MoveGen::generatePseudoMoves(const Position& pos) {
  std::vector<MoveEntry> moves;

  U64 piecesBB[PIECE_TYPE_NUM];
  U64 myBoard = pos.getColorBB(pos.getColorToMove());
  U64 oppBoard = pos.getColorBB(Color(!pos.getColorToMove()));
  Piece pieceOffset = pos.getColorToMove() == WHITE ? W_PAWN : B_PAWN;

  piecesBB[PAWN] = pos.getPieceBB(Piece(pieceOffset + PAWN));
  piecesBB[KNIGHT] = pos.getPieceBB(Piece(pieceOffset + KNIGHT));
  piecesBB[BISHOP] = pos.getPieceBB(Piece(pieceOffset + BISHOP));
  piecesBB[ROOK] = pos.getPieceBB(Piece(pieceOffset + ROOK));
  piecesBB[QUEEN] = pos.getPieceBB(Piece(pieceOffset + QUEEN));
  piecesBB[KING] = pos.getPieceBB(Piece(pieceOffset + KING));

//  if(pos.getColorToMove() == WHITE) {
//    piecesMovesBB[PAWN] = genPawnMovesBB<WHITE>(piecesBB[PAWN], myBoard, oppBoard, pos.getEpSquare());
//  } else {
//    piecesMovesBB[PAWN] = genPawnMovesBB<BLACK>(piecesBB[PAWN], myBoard, oppBoard, pos.getEpSquare());
//  }
//  piecesMovesBB[KNIGHT] = genKnightMovesBB(piecesBB[KNIGHT], myBoard);
//  piecesMovesBB[BISHOP] = genBishopMovesBB(piecesBB[BISHOP], myBoard, oppBoard);
//  piecesMovesBB[ROOK] = genRookMovesBB(piecesBB[ROOK], myBoard, oppBoard);
//  piecesMovesBB[QUEEN] = genQueenMovesBB(piecesBB[QUEEN], myBoard, oppBoard);
//  piecesMovesBB[KING] = genKingMovesBB(piecesBB[KING], myBoard);

  for(Piece p : PIECES) {
    U64 allPieces = piecesBB[p];

    // Process each individual piece
    while(allPieces) {
      U64 pieceOrig = Bitboard::popLsb(allPieces);
//      U64 pieceMoves = piecesMovesBB[p];
//      while(pieceMoves) {
//        U64 pieceDest = Bitboard::popLsb(pieceMoves);
//      }
    }
  }

  return moves;
}

