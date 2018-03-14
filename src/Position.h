#ifndef SRC_POSITION_H_
#define SRC_POSITION_H_

#include "Types.h"
#include "Bitboard.h"

class Position {
public:

private:
  U64 piecesByType[Piece::PIECE_NUM];
  U64 piecesByColor[Color::COLOR_NUM];

  int ply;
  Color colorToMove;
};

#endif /* SRC_POSITION_H_ */
