#ifndef SRC_POSITION_H_
#define SRC_POSITION_H_

#include <string>
#include <sstream>
#include <cctype>

#include "Types.h"
#include "Bitboard.h"

class Position {
public:
  Position(std::string fen=STARTING_POSITION);
private:
  // Bitboards for each player's pieces
  U64 piecesByType[Piece::PIECE_NUM];
  // Bitboards for each player
  U64 piecesByColor[Color::COLOR_NUM];

  // Half-moves from the start of the game
  int ply;
  // The number of half-moves since the last capture of pawn move
  int fiftyMoveClock;
  // The player whose turn it currently is
  Color colorToMove;
  // The en passant square (that can be moved to in an en passant capture)
  Square epSquare;
  // The zobrist hash of this board position
  U64 signature;
  // Castling rights of both players
  int castlingRights;

  static const std::string STARTING_POSITION;
};

#endif /* SRC_POSITION_H_ */
