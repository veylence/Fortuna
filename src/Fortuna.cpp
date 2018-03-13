#include <iostream>
#include <vector>
#include <chrono>

// Uncomment to disable assert()
// #define NDEBUG
#include "Bitboard.h"
#include "GenerateMagics.h"
#include "MoveGenerator.h"

int main() {
  std::vector<U64> rookOccupancyMasks = Magics::generateRookOccupancyMasks();
  std::vector<std::vector<U64> > rookOccupancyMaskVariations = Magics::generateOccupancyVariations(rookOccupancyMasks);
  std::vector<std::vector<U64> > rookAttackSets = Magics::generateRookAttackSets(rookOccupancyMaskVariations);

  std::vector<U64> bishopOccupancyMasks = Magics::generateBishopOccupancyMasks();
  std::vector<std::vector<U64> > bishopOccupancyMaskVariations = Magics::generateOccupancyVariations(bishopOccupancyMasks);
  std::vector<std::vector<U64> > bishopAttackSets = Magics::generateBishopAttackSets(bishopOccupancyMaskVariations);

  //  std::vector<U64> magics = Magics::generateMagics(bishopOccupancyMasks, bishopOccupancyMaskVariations, bishopAttackSets);
  //  for(const auto& m : magics) {
  //    std::cout << std::hex << m << std::endl;
  //  }

//  MoveGenerator::init();
//  int square = 36;
//  U64 occupancyMask = rookOccupancyMaskVariations[square][500]; // A1, variation 1000
//  int index = (occupancyMask * MoveGenerator::MAGIC_NUMBERS_ROOKS[square]) >> MoveGenerator::MAGIC_NUMBER_SHIFTS_ROOK[square];
//  U64 moves = MoveGenerator::ROOK_MOVES[square][index];
//
//  std::cout << Bitboard::toString(occupancyMask) << std::endl;
//  std::cout << Bitboard::toString(moves) << std::endl;

  auto start = std::chrono::high_resolution_clock::now();
  U64 x = 1;
  for(U64 i = 1; i < 100000000; i++) {
    x *= i;
    x >>= 32;
  }
  auto time = std::chrono::high_resolution_clock::now() - start;
  std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(time).count() << std::endl;
//  std::cout << x << std::endl;
}
