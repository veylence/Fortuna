#ifndef SRC_POSITION_H_
#define SRC_POSITION_H_

#include <string>
#include <sstream>
#include <cctype>
#include <random>
#include <iostream>

#include "Types.h"
#include "Bitboard.h"

class Position {
public:
  static void init();

  Position(std::string fen=STARTING_POSITION);
  friend std::ostream& operator<<(std::ostream& os, const Position& pos);

  Color getColorToMove() const { return colorToMove; };
  Square getEpSquare() const { return epSquare; };
  U64 getPieceBB(Piece piece) const { return piecesByType[piece]; };
  U64 getColorBB(Color color) const { return piecesByColor[color]; };
private:
  // Bitboards for each player's pieces
  U64 piecesByType[Piece::PIECE_MAX];
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

  void addPiece(Piece piece, int square);
  void removePiece(Piece piece, int square);
  void movePiece(Piece piece, int orig, int dest);

  static const std::string STARTING_POSITION;
};

#endif /* SRC_POSITION_H_ */
