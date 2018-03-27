#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>

// Uncomment to disable assertions
// #define NDEBUG
#include "Bitboard.h"
#include "Position.h"
#include "GenerateMagics.h"
#include "MoveGenerator.h"
#include "Types.h"

int main() {
  Position::init();
  MoveGen::init();

  Position pos;
  std::cout << pos << std::endl;

  auto start = std::chrono::high_resolution_clock::now();

  U64 sq = 1ULL << 0;
//  U64 b = MoveGen::genKnightMoves(sq, 1ULL << 10);
//  U64 b = MoveGen::genBishopMoves(sq, 1ULL << 10, 0);
  clock_t c = clock();
  U64 b = 0;
  for(int i = 0; i < 100000000; ++i) {
//  b = MoveGen::genRookMovesBB(sq, 1ULL << 32, 1ULL << 32);
//  b |= MoveGen::genPawnMovesBB<WHITE, SQ_NONE>(sq, b, b);
//  b = MoveGen::genQueenMovesBB(sq, b, b);
//  b = MoveGen::genKnightMovesBB(sq, 1ULL << 32);
//  b |= MoveGen::genKingMovesBB(sq, b);
  }
  std::cout << "BB: " << b << std::endl;
//  std::cout << Bitboard::toString(sq) << std::endl;
//  std::cout << Bitboard::toString(b) << std::endl;
  std::cout << 1.f*(clock() - c)/CLOCKS_PER_SEC << std::endl;
  auto time = std::chrono::high_resolution_clock::now() - start;
  std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(time).count() << std::endl;
}
