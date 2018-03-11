#include <iostream>
#include <vector>

#include "Types.h"
#include "GenerateMagics.h"
#include "Bitboard.h"

std::vector<U64> Magics::generateRookOccupancyMasks() {
  std::vector<U64> rookMasks;
  for (int square = 0; square < Square::NUM; square++) {
    U64 mask = 0;

    // North file
    for (int i = square + N; i < Square::NUM - SIZE; i += N) {
      mask |= 1ULL << i;
    }
    // South file
    for (int i = square + S; i >= SIZE; i += S) {
      mask |= 1ULL << i;
    }
    // West rank
    for (int i = square + W; i % SIZE != 0 && i % SIZE != SIZE - 1; i += W) {
      mask |= 1ULL << i;
    }
    // East rank
    for (int i = square + E; i % SIZE != 0 && i % SIZE != SIZE - 1 && i >= 0; i += E) {
      mask |= 1ULL << i;
    }

    rookMasks.push_back(mask);
  }
  return rookMasks;
}

std::vector<U64> Magics::generateBishopOccupancyMasks() {
  std::vector<U64> bishopMasks;
  for (int square = 0; square < Square::NUM; square++) {
    U64 mask = 0;

    // North-east diagonal
    for (int i = square + NE; i % SIZE != 0 && i % SIZE != SIZE - 1 && i < Square::NUM - SIZE; i += NE) {
      mask |= 1ULL << i;
    }
    // South-east diagonal
    for (int i = square + SE; i % SIZE != 0 && i % SIZE != SIZE - 1 && i >= SIZE; i += SE) {
      mask |= 1ULL << i;
    }
    // South-west diagonal
    for (int i = square + SW; i % SIZE != 0 && i % SIZE != SIZE - 1 && i >= SIZE; i += SW) {
      mask |= 1ULL << i;
    }
    // North-west diagonal
    for (int i = square + NW; i % SIZE != 0 && i % SIZE != SIZE - 1 && i < Square::NUM - SIZE; i += NW) {
      mask |= 1ULL << i;
    }

    bishopMasks.push_back(mask);
  }
  return bishopMasks;
}

std::vector<std::vector<U64> > Magics::generateOccupancyVariations(std::vector<U64> masks) {
  std::vector<std::vector<U64> > variations;

  // Create all variations for each mask
  for(int square = 0; square < Square::NUM; square++) {
    std::vector<U64> squareVariations;
    U64 mask = masks[square];

    // Calculate all 2^count variations for this occupancy mask, where count
    // is the number of 1 bits in the mask.
    std::vector<U64> bits;
    while (mask) {
      bits.push_back(Bitboard::popLsb(mask));
    }
    bool acc[bits.size()];
    generateVariations(bits, acc, squareVariations);
    assert(squareVariations.size() == (1 << bits.size()));

    variations.push_back(squareVariations);
  }

  return variations;
}

void Magics::generateVariations(std::vector<U64>& masks, bool acc[], std::vector<U64>& variations, int bitIndex) {
  // Base case: Create the variation using what has been set in the accumulator
  if(bitIndex >= masks.size()) {
    U64 variation = 0;
    for(int i = 0; i < masks.size(); i++) {
      if(acc[i]) {
        variation |= masks[i];
      }
    }
    variations.push_back(variation);
    return;
  }

  // Generate combinations for both possible values of this index (true + false)
  acc[bitIndex] = true;
  generateVariations(masks, acc, variations, bitIndex + 1);
  acc[bitIndex] = false;
  generateVariations(masks, acc, variations, bitIndex + 1);
}
