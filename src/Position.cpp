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

  for(Piece p : PIECES) {
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

Position::Position(std::string fen) :
    signature(0),
    castlingRights(NO_CASTLING) {
  for(Piece p : PIECES) {
    piecesByType[p] = 0;
  }
  piecesByColor[WHITE] = 0;
  piecesByColor[BLACK] = 0;

  std::istringstream in(fen);
  in >> std::noskipws; // Set input to read whitespace
  char token;

  // 1. Board/pieces
  int square = A8;
  while((in >> token) && !isspace(token)) {
    if(isdigit(token)) {
      square += token - '0'; // Skip forward this many squares
    } else if(token == '/') {
      square += 2 * S; // Move to the start of the next row down
    } else {
      addPiece(Piece(PIECE_CHARS.find(token)), square);
      square++; // Move 1 square right
    }
  }

  // 2. Player to move
  in >> token;
  if(token == 'w') {
    colorToMove = WHITE;
    signature ^= Zobrist::turn;
  } else {
    colorToMove = BLACK;
  }
  in >> token; // Space

  // 3. Castling rights
  while((in >> token) && !isspace(token)) {
    if(token == 'K') {
      castlingRights |= W_KINGSIDE;
    } else if(token == 'Q') {
      castlingRights |= W_QUEENSIDE;
    } else if(token == 'k') {
      castlingRights |= B_KINGSIDE;
    } else if(token == 'q'){
      castlingRights |= B_QUEENSIDE;
    }
  }
  signature ^= Zobrist::castling[castlingRights];

  // 4. En passant
  in >> token;
  if(token != '-') {
    File file = File(token - 'a');
    in >> token;
    Rank rank = Rank(token - '1');
    epSquare = Square(rank * SIZE + file);

    signature ^= Zobrist::enpassant[file];
  }

  // 5. 50 move clock
  in >> std::skipws >> fiftyMoveClock;

  // 6. Fullmove clock
  in >> ply;
  // Convert the FEN's fullmove count that begins at 1 and increments after
  // black's turn to a ply value that begins at 0 and increments every move
  ply = std::max(2 * (ply - 1), 0) + (colorToMove == BLACK ? 1 : 0);
}

void Position::addPiece(Piece piece, int square) {
  U64 squareBB = 1ULL << square;
  piecesByType[piece] |= squareBB;
  piecesByColor[colorOf(piece)] |= squareBB;
  signature ^= Zobrist::pieces[piece][square];
}

void Position::removePiece(Piece piece, int square) {
  U64 squareBB = ~(1ULL << square);
  piecesByType[piece] &= squareBB;
  piecesByColor[colorOf(piece)] &= squareBB;
  signature ^= Zobrist::pieces[piece][square];
}

void Position::movePiece(Piece piece, int orig, int dest) {
  removePiece(piece, orig);
  addPiece(piece, dest);
}

std::ostream& operator<<(std::ostream& os, const Position& pos) {
  std::string s = "";

  // Process all ranks
  for (int rank = 7; rank >= 0; rank--) {
    // Add rank number
    s += (char) ('1' + rank);
    // Add each square in this rank
    for (int file = 0; file < 8; file++) {
      U64 square = 1ULL << (rank * 8 + file);
      Piece piece = PIECE_NONE;
      for(Piece p : PIECES) {
        if(pos.piecesByType[p] & square) {
          piece = Piece(p);
          break;
        }
      }

      s += ' ';
      if (piece != PIECE_NONE) {
        s += PIECE_CHARS.at(piece);
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

  os << s;
  return os;
}

