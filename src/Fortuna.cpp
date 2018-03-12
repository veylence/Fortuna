#include <iostream>
#include <vector>

// Uncomment to disable assert()
// #define NDEBUG
#include "Bitboard.h"
#include "GenerateMagics.h"

int main() {
  std::vector<U64> rookOccupancyMasks = Magics::generateRookOccupancyMasks();
  std::vector<std::vector<U64> > rookOccupancyMaskVariations = Magics::generateOccupancyVariations(rookOccupancyMasks);
  std::vector<std::vector<U64> > rookAttackSets = Magics::generateRookAttackSets(rookOccupancyMaskVariations);

  std::vector<U64> bishopOccupancyMasks = Magics::generateBishopOccupancyMasks();
  std::vector<std::vector<U64> > bishopOccupancyMaskVariations = Magics::generateOccupancyVariations(bishopOccupancyMasks);
  std::vector<std::vector<U64> > bishopAttackSets = Magics::generateBishopAttackSets(bishopOccupancyMaskVariations);

  std::vector<U64> magics = Magics::generateMagics(bishopOccupancyMasks, bishopOccupancyMaskVariations, bishopAttackSets);
  for(const auto& m : magics) {
    std::cout << std::hex << m << std::endl;
  }
}
