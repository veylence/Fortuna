#include <iostream>
#include <vector>

// Uncomment to disable assert()
// #define NDEBUG
#include "Bitboard.h"
#include "GenerateMagics.h"

int main() {
  //	U64 mask = 0x007E010101010100ULL;
  //	U64 magic = 0x48FFFE99FECFAA00ULL;
  //	U64 index = (mask * magic) >> (64 - 11);
  //
  //	std::cout << Bitboard::toString(mask) << std::endl;
  //	std::cout << Bitboard::toString(index) << std::endl;
  //	std::cout << index << std::endl;
  //
  //	std::cout << Bitboard::toString(0x40201008040200ULL) << std::endl;

//  std::vector<U64> rookMasks = Magics::generateRookOccupancyMasks();
//  for(const auto& it : rookMasks) {
//    std::cout << Bitboard::toString(it) << std::endl;
//    std::cout << 64-Bitboard::sparseCount(it) << std::endl;
//  }
//  std::cout << Bitboard::toString(rookMasks[C3]) << std::endl;

  //  std::vector<U64> bishopMasks = Magics::generateBishopOccupancyMasks();
  //  for(const auto& it : bishopMasks) {
  //    std::cout << Bitboard::toString(it) << std::endl;
  //  }

  std::vector<U64> bits;
  bits.push_back(1ULL << 0);
  bits.push_back(1ULL << 1);
  bits.push_back(1ULL << 2);
  std::vector<U64> variations;
  bool acc[bits.size()];
  Magics::generateVariations(bits, acc, variations);
  for(auto it : variations) {
    std::cout << it << std::endl;
  }

  std::vector<std::vector<U64> > vars = Magics::generateOccupancyVariations(Magics::generateRookOccupancyMasks());
  std::cout << std::endl << vars[0].size() << std::endl;
  std::cout << std::endl << Bitboard::toString(vars[0][5]) << std::endl;
}
