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

namespace {

U64 genKnightMovesBB(U64 piece, U64 myBoard) {
  int index = Bitboard::bsfIndex(piece);
  return MoveGen::KNIGHT_MOVES[index] & ~myBoard;
}

U64 genBishopMovesBB(U64 piece, U64 myBoard, U64 oppBoard) {
  int square = Bitboard::bsfIndex(piece);
  assert(MoveGen::BISHOP_MOVES[square] != nullptr);
  U64 occupancy = MoveGen::OCCUPANCY_MASKS_BISHOP[square] & (myBoard | oppBoard);
  int magicIndex = (occupancy * MoveGen::MAGIC_NUMBERS_BISHOPS[square]) >> MoveGen::MAGIC_NUMBER_SHIFTS_BISHOP[square];

  return MoveGen::BISHOP_MOVES[square][magicIndex] & ~myBoard;
}

U64 genRookMovesBB(U64 piece, U64 myBoard, U64 oppBoard) {
  int square = Bitboard::bsfIndex(piece);
  assert(MoveGen::ROOK_MOVES[square] != nullptr);
  U64 occupancy = MoveGen::OCCUPANCY_MASKS_ROOK[square] & (myBoard | oppBoard);
  int magicIndex = (occupancy * MoveGen::MAGIC_NUMBERS_ROOKS[square]) >> MoveGen::MAGIC_NUMBER_SHIFTS_ROOK[square];

  return MoveGen::ROOK_MOVES[square][magicIndex] & ~myBoard;
}

U64 genQueenMovesBB(U64 piece, U64 myBoard, U64 oppBoard) {
  return genBishopMovesBB(piece, myBoard, oppBoard) | genRookMovesBB(piece, myBoard, oppBoard);
}

U64 genKingMovesBB(U64 piece, U64 myBoard) {
  int index = Bitboard::bsfIndex(piece);
  return MoveGen::KING_MOVES[index] & ~myBoard;
}

template<Color player>
U64 genPawnMovesBB(U64 pieces, U64 myBoard, U64 oppBoard, U64 epSquareBB) {
  assert(player == WHITE || player == BLACK);

  constexpr Direction up      = (player == WHITE) ? N : S;                   // Direction pawns move
  constexpr Direction upLeft  = (player == WHITE) ? NW : SE;                 // Capture left
  constexpr Direction upRight = (player == WHITE) ? NE : SW;                 // Capture right
  constexpr U64 rank3         = (player == WHITE) ? RANK_3_BB : RANK_6_BB;   // One move from start rank
  constexpr U64 leftMask      = (player == WHITE) ? ~FILE_A_BB : ~FILE_H_BB; // Leftmost file mask
  constexpr U64 rightMask     = (player == WHITE) ? ~FILE_H_BB : ~FILE_A_BB; // Rightmost file mask
  // Bitboard of empty squares that can be moved to (i.e. all non-blockers)
  U64 empty = ~(myBoard | oppBoard);

  // Moving one square up
  U64 onePush = shift<up>(pieces) & empty;
  // Moving two squares up (only for pawns on the starting rank)
  U64 twoPush = shift<up>(onePush & rank3) & empty;
  // Capturing, either normally or by en passant
  U64 capture = shift<upLeft>(pieces) & rightMask & (oppBoard | epSquareBB);
  capture    |= shift<upRight>(pieces) & leftMask & (oppBoard | epSquareBB);

  return onePush | twoPush | capture;
}
}

std::vector<MoveEntry> MoveGen::generatePseudoMoves(const Position& pos) {
  std::vector<MoveEntry> moves;

  U64 myBoard = pos.getColorBB(pos.getColorToMove());
  U64 oppBoard = pos.getColorBB(Color(!pos.getColorToMove()));
  U64 epSquareBB = pos.getEpSquare() == SQ_NONE ? 0 : 1ULL << pos.getEpSquare();
  Piece pieceOffset = pos.getColorToMove() == WHITE ? W_PAWN : B_PAWN;

  int total = 0;

  U64 pieces = pos.getPieceBB(Piece(pieceOffset + PAWN));
  while(pieces) {
    U64 pieceOrig = Bitboard::popLsb(pieces);
    Color color = pos.getColorToMove();
    U64 pieceMoves;
    if(color == WHITE) {
      pieceMoves = genPawnMovesBB<WHITE>(pieceOrig, myBoard, oppBoard, epSquareBB);
    } else {
      pieceMoves = genPawnMovesBB<BLACK>(pieceOrig, myBoard, oppBoard, epSquareBB);
    }
    while(pieceMoves) {
      U64 pieceDest = Bitboard::popLsb(pieceMoves);
      total++;
    }
  }

  pieces = pos.getPieceBB(Piece(pieceOffset + KNIGHT));
  while(pieces) {
    U64 pieceOrig = Bitboard::popLsb(pieces);
    U64 pieceMoves = genKnightMovesBB(pieceOrig, myBoard);
    while(pieceMoves) {
      U64 pieceDest = Bitboard::popLsb(pieceMoves);
      total++;
    }
  }

  pieces = pos.getPieceBB(Piece(pieceOffset + BISHOP));
  while(pieces) {
    U64 pieceOrig = Bitboard::popLsb(pieces);
    U64 pieceMoves = genBishopMovesBB(pieceOrig, myBoard, oppBoard);
    while(pieceMoves) {
      U64 pieceDest = Bitboard::popLsb(pieceMoves);
      total++;
    }
  }

  pieces = pos.getPieceBB(Piece(pieceOffset + ROOK));
  while(pieces) {
    U64 pieceOrig = Bitboard::popLsb(pieces);
    U64 pieceMoves = genRookMovesBB(pieceOrig, myBoard, oppBoard);
    while(pieceMoves) {
      U64 pieceDest = Bitboard::popLsb(pieceMoves);
      total++;
    }
  }

  pieces = pos.getPieceBB(Piece(pieceOffset + QUEEN));
  while(pieces) {
    U64 pieceOrig = Bitboard::popLsb(pieces);
    U64 pieceMoves = genQueenMovesBB(pieceOrig, myBoard, oppBoard);
    while(pieceMoves) {
      U64 pieceDest = Bitboard::popLsb(pieceMoves);
      total++;
    }
  }

  pieces = pos.getPieceBB(Piece(pieceOffset + KING));
  while(pieces) {
    U64 pieceOrig = Bitboard::popLsb(pieces);
    U64 pieceMoves = genKingMovesBB(pieceOrig, myBoard);
    while(pieceMoves) {
      U64 pieceDest = Bitboard::popLsb(pieceMoves);
      total++;
    }
  }

  return moves;
}

