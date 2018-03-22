#include <iostream>
#include <vector>
#include <chrono>

// Uncomment to disable assert()
// #define NDEBUG
#include "Bitboard.h"
#include "GenerateMagics.h"
#include "MoveGenerator.h"
#include "Types.h"

int main() {
  std::vector<U64> rookOccupancyMasks = Magics::generateRookOccupancyMasks();
  std::vector<std::vector<U64> > rookOccupancyMaskVariations = Magics::generateOccupancyVariations(rookOccupancyMasks);
  std::vector<std::vector<U64> > rookAttackSets = Magics::generateRookAttackSets(rookOccupancyMaskVariations);

  std::vector<U64> bishopOccupancyMasks = Magics::generateBishopOccupancyMasks();
  std::vector<std::vector<U64> > bishopOccupancyMaskVariations = Magics::generateOccupancyVariations(bishopOccupancyMasks);
  std::vector<std::vector<U64> > bishopAttackSets = Magics::generateBishopAttackSets(bishopOccupancyMaskVariations);

//    std::vector<U64> magics = Magics::generateMagics(rookOccupancyMasks, rookOccupancyMaskVariations, rookAttackSets);
//    std::vector<U64> magics = Magics::generateMagics(bishopOccupancyMasks, bishopOccupancyMaskVariations, bishopAttackSets);
  //  for(const auto& m : magics) {
  //    std::cout << std::hex << m << std::endl;
  //  }

  auto start = std::chrono::high_resolution_clock::now();

  MoveGen::init();
  U64 sq = 1ULL << 0;
//  U64 b = MoveGen::genKnightMoves(sq, 1ULL << 10);
//  U64 b = MoveGen::genBishopMoves(sq, 1ULL << 10, 0);
  for(int i = 0; i < 100000000; i++) {
  U64 b = MoveGen::genRookMoves(sq, 1ULL << 32, 1ULL << 32);
//  U64 b = MoveGen::genKnightMoves(sq, 1ULL << 32);
  }
//  std::cout << Bitboard::toString(sq) << std::endl;
//  std::cout << Bitboard::toString(b) << std::endl;

  auto time = std::chrono::high_resolution_clock::now() - start;
  std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(time).count() << std::endl;
}
