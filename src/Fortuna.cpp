#include <iostream>
#include <vector>

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
//  }

  std::vector<U64> bishopMasks = Magics::generateBishopOccupancyMasks();
  for(const auto& it : bishopMasks) {
    std::cout << Bitboard::toString(it) << std::endl;
  }
}
