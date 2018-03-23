#include "Position.h"

const std::string Position::STARTING_POSITION = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

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
