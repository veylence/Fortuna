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

  MoveGen::generatePseudoMoves(pos);

//  auto start = std::chrono::high_resolution_clock::now();

  U64 sq = 1ULL << 0;
//  U64 b = MoveGen::genKnightMoves(sq, 1ULL << 10);
//  U64 b = MoveGen::genBishopMoves(sq, 1ULL << 10, 0);
  clock_t c = clock();
  U64 b = 1;
  for(U64 i = 1; i <= 5072213; ++i) {
    MoveGen::generatePseudoMoves(pos);
  }

  std::cout << "b: " << b << std::endl;
//  std::cout << Bitboard::toString(sq) << std::endl;
//  std::cout << Bitboard::toString(b) << std::endl;
  std::cout << double(clock() - c)/CLOCKS_PER_SEC/1.0 << std::endl;
//  auto time = std::chrono::high_resolution_clock::now() - start;
//  std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(time).count() << std::endl;
}


/*
 0x1,
0x2,
0x4,
0x8,
0x10,
0x20,
0x40,
0x80,
0x100,
0x200,
0x400,
0x800,
0x1000,
0x2000,
0x4000,
0x8000,
0x10000,
0x20000,
0x40000,
0x80000,
0x100000,
0x200000,
0x400000,
0x800000,
0x1000000,
0x2000000,
0x4000000,
0x8000000,
0x10000000,
0x20000000,
0x40000000,
0x80000000,
0x100000000,
0x200000000,
0x400000000,
0x800000000,
0x1000000000,
0x2000000000,
0x4000000000,
0x8000000000,
0x10000000000,
0x20000000000,
0x40000000000,
0x80000000000,
0x100000000000,
0x200000000000,
0x400000000000,
0x800000000000,
0x1000000000000,
0x2000000000000,
0x4000000000000,
0x8000000000000,
0x10000000000000,
0x20000000000000,
0x40000000000000,
0x80000000000000,
0x100000000000000,
0x200000000000000,
0x400000000000000,
0x800000000000000,
0x1000000000000000,
0x2000000000000000,
0x4000000000000000,
0x8000000000000000,
 */
