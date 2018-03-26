#include "Position.h"

const std::string Position::STARTING_POSITION = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

namespace Zobrist {
  U64 pieces[PIECE_NUM][SQ_NUM];
  U64 enpassant[FILE_NUM];
  U64 castling[CASTLING_NUM];
  U64 turn;
}

void Position::init() {
  // 64-bit random number generator
  std::random_device rd;
  std::mt19937_64 mt(rd());
  std::uniform_int_distribution<U64> rand;

  for(int p = W_PAWN; p <= B_KING; p++) {
    for(int s = A1; s <= H8; s++) {
      Zobrist::pieces[p][s] = rand(mt);
    }
  }

  for(int f = FILE_A; f <= FILE_H; f++) {
    Zobrist::enpassant[f] = rand(mt);
  }

  for(int i = 0; i < CASTLING_NUM; i++) {
    Zobrist::castling[i] = rand(mt);
  }

  Zobrist::turn = rand(mt);
}

Position::Position(std::string fen) {
  std::istringstream in(fen);
  char token;

  // 1. Parse board/pieces
  int square = A8;
  while((in >> token) && !isspace(token)) {
    if(isdigit(token)) {
      square += token - '0';
    } else if(token == '/') {
      square += 2 * S;
    } else {
      square++;
    }
  }
}

void Position::addPiece(Piece piece, int square) {
  piecesByType[piece] |= 1ULL << square;
  signature ^= Zobrist::pieces[piece][square];
}

void Position::removePiece(Piece piece, int square) {
  piecesByType[piece] &= ~(1ULL << square);
  signature ^= Zobrist::pieces[piece][square];
}

void Position::movePiece(Piece piece, int orig, int dest) {
  removePiece(piece, orig);
  addPiece(piece, dest);
}

