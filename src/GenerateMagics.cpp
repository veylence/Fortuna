#include <iostream>
#include <vector>

#include "Types.h"
#include "GenerateMagics.h"
#include "Bitboard.h"

std::vector<U64> Magics::generateRookOccupancyMasks() {
  std::vector<U64> rookMasks;
  for (int square = 0; square < Square::SQ_NUM; square++) {
    U64 mask = 0;

    // North file
    for (int i = square + N; i < Square::SQ_NUM - SIZE; i += N) {
      mask |= 1ULL << i;
    }
    // South file
    for (int i = square + S; i >= SIZE; i += S) {
      mask |= 1ULL << i;
    }
    // East rank
    for (int i = square + E; i % SIZE != 0 && i % SIZE != SIZE - 1; i += E) {
      mask |= 1ULL << i;
    }
    // West rank
    for (int i = square + W; i % SIZE != 0 && i % SIZE != SIZE - 1 && i >= 0; i += W) {
      mask |= 1ULL << i;
    }

    rookMasks.push_back(mask);
  }
  return rookMasks;
}

std::vector<U64> Magics::generateBishopOccupancyMasks() {
  std::vector<U64> bishopMasks;
  for (int square = 0; square < Square::SQ_NUM; square++) {
    U64 mask = 0;

    // North-east diagonal
    for (int i = square + NE; i % SIZE != 0 && i % SIZE != SIZE - 1 && i < Square::SQ_NUM - SIZE; i += NE) {
      mask |= 1ULL << i;
    }
    // South-west diagonal
    for (int i = square + SW; i % SIZE != 0 && i % SIZE != SIZE - 1 && i >= SIZE; i += SW) {
      mask |= 1ULL << i;
    }
    // North-west diagonal
    for (int i = square + NW; i % SIZE != 0 && i % SIZE != SIZE - 1 && i < Square::SQ_NUM - SIZE; i += NW) {
      mask |= 1ULL << i;
    }
    // South-east diagonal
    for (int i = square + SE; i % SIZE != 0 && i % SIZE != SIZE - 1 && i >= SIZE; i += SE) {
      mask |= 1ULL << i;
    }

    bishopMasks.push_back(mask);
  }
  return bishopMasks;
}

std::vector<std::vector<U64> > Magics::generateOccupancyVariations(std::vector<U64> masks) {
  std::vector<std::vector<U64> > variations;

  // Create all variations for each mask
  for(int square = 0; square < Square::SQ_NUM; square++) {
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

void Magics::generateVariations(std::vector<U64>& masks, bool acc[],
                                std::vector<U64>& variations, int bitIndex) {
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

std::vector<std::vector<U64> > Magics::generateRookAttackSets(const std::vector<std::vector<U64> >& variations) {
  std::vector<std::vector<U64> > rookAttackSet;

  // Create attack set for all variations of each square
  for(int square = 0; square < variations.size(); square++) {
    std::vector<U64> squareVariationsAttackSets;

    // Create attack set for each variation for this square
    for(int i = 0; i < variations[square].size(); i++) {
      U64 variation = variations[square][i];
      int j;
      U64 attackSet = 0;

//      for(j = square + N; j < Square::NUM - SIZE && !(variation & (1ULL << j)); j += N);
//      if (j >= 0 && j < Square::NUM) {
//        attackSet |= (1ULL << j);
//      }
//      for(j = square + S; j >= SIZE && !(variation & (1ULL << j)); j += S);
//      if (j >= 0 && j < Square::NUM) {
//        attackSet |= (1ULL << j);
//      }
//      for(j = square + E; j % SIZE != 0 && j % SIZE != SIZE - 1 && !(variation & (1ULL << j)); j += E);
//      if (j >= 0 && j < Square::NUM) {
//        attackSet |= (1ULL << j);
//      }
//      for(j = square + W; j % SIZE != 0 && j % SIZE != SIZE - 1 && j >= 0 && !(variation & (1ULL << j)); j += W);
//      if (j >= 0 && j < Square::NUM) {
//        attackSet |= (1ULL << j);
//      }
      for (j = square + N; j < Square::SQ_NUM; j += N) {
        attackSet |= (1ULL << j);
        if (variation & (1ULL << j)) {
          break;
        }
      }
      for (j = square + S; j >= 0; j += S) {
        attackSet |= (1ULL << j);
        if (variation & (1ULL << j)) {
          break;
        }
      }
      for (j = square + E; j % SIZE != 0; j += E) {
        attackSet |= (1ULL << j);
        if (variation & (1ULL << j)) {
          break;
        }
      }
      for (j = square + W; j % SIZE != SIZE - 1 && j >= 0; j += W) {
        attackSet |= (1ULL << j);
        if (variation & (1ULL << j)) {
          break;
        }
      }

      squareVariationsAttackSets.push_back(attackSet);
    }

    rookAttackSet.push_back(squareVariationsAttackSets);
  }

  return rookAttackSet;
}

std::vector<std::vector<U64> > Magics::generateBishopAttackSets(const std::vector<std::vector<U64> >& variations) {
  std::vector<std::vector<U64> > bishopAttackSet;

  // Create attack set for all variations of each square
  for(int square = 0; square < variations.size(); square++) {
    std::vector<U64> squareVariationsAttackSets;

    // Create attack set for each variation for this square
    for(int i = 0; i < variations[square].size(); i++) {
      U64 variation = variations[square][i];
      int j;
      U64 attackSet = 0;

//      for(j = square + NE; j % SIZE != 0 && j % SIZE != SIZE - 1 && j < Square::NUM - SIZE && !(variation & (1ULL << j)); j += NE);
//      if (j >= 0 && j < Square::NUM) {
//        attackSet |= (1ULL << j);
//      }
//      for(j = square + SW; j % SIZE != 0 && j % SIZE != SIZE - 1 && j >= SIZE && !(variation & (1ULL << j)); j += SW);
//      if (j >= 0 && j < Square::NUM) {
//        attackSet |= (1ULL << j);
//      }
//      for(j = square + NW; j % SIZE != 0 && j % SIZE != SIZE - 1 && j < Square::NUM - SIZE && !(variation & (1ULL << j)); j += NW);
//      if (j >= 0 && j < Square::NUM) {
//        attackSet |= (1ULL << j);
//      }
//      for(j = square + SE; j % SIZE != 0 && j % SIZE != SIZE - 1 && j >= SIZE && !(variation & (1ULL << j)); j += SE);
//      if (j >= 0 && j < Square::NUM) {
//        attackSet |= (1ULL << j);
//      }
      for(j = square + NE; j % SIZE != 0 && j < Square::SQ_NUM; j += NE) {
        attackSet |= (1ULL << j);
        if (variation & (1ULL << j)) {
          break;
        }
      }
      for(j = square + SW; j % SIZE != SIZE - 1 && j >= 0; j += SW) {
        attackSet |= (1ULL << j);
        if (variation & (1ULL << j)) {
          break;
        }
      }
      for(j = square + NW; j % SIZE != SIZE - 1 && j < Square::SQ_NUM; j += NW) {
        attackSet |= (1ULL << j);
        if (variation & (1ULL << j)) {
          break;
        }
      }
      for(j = square + SE; j % SIZE != 0 && j >= 0; j += SE) {
        attackSet |= (1ULL << j);
        if (variation & (1ULL << j)) {
          break;
        }
      }

      squareVariationsAttackSets.push_back(attackSet);
    }

    bishopAttackSet.push_back(squareVariationsAttackSets);
  }

  return bishopAttackSet;
}

std::vector<U64> Magics::generateMagics(std::vector<U64> masks,
                                        std::vector<std::vector<U64> > variations,
                                        std::vector<std::vector<U64> > attackSets) {
  // 64-bit random number generator
  std::random_device rd;
  std::mt19937_64 mt(rd());
  std::uniform_int_distribution<U64> rand;

  std::vector<U64> magics;

  // Generate magic for each square
  for(int square = 0; square < Square::SQ_NUM; square++) {
    square = A1;
    int bitCount = Bitboard::popCount(masks[square]);
    int variationCount = variations[square].size();

    // Table of where each variation mask will be mapped to after the magic
    // transformation is applied.
    U64 used[variationCount];
    // The candidate magic
    U64 magic;
    // Whether this magic candidate is invalid
    bool invalid;

    int attempts = 0;
    int usedCount = 0;
    do {
      usedCount = 0;
      attempts++;

      // Choose a new candidate magic with few 1 bits
      magic = rand(mt) & rand(mt) & rand(mt);// & rand(mt);
      // Reset table
      for(int i = 0; i < variationCount; i++) {
        used[i] = 0;
      }

      // Test this magic for all occupancy variation masks
      invalid = false;

      for(int i = 0; !invalid && i < variationCount; i++) {
        // Do magic transformation to obtain index
        int index = (variations[square][i] * magic) >> (64 - bitCount);

        if(!used[index]) {
          // If this index isn't already mapped to, map this attack set to it
          used[index] = attackSets[square][i];
          usedCount++;
        } else if(used[index] != attackSets[square][i]) {
          // If this index is already mapped by a different attack set, this
          // magic is invalid
          invalid = true;
        }
      }
    } while(invalid);
    if(usedCount == variationCount) {
      square--;
//      std::cout << 1 << std::endl;
    } else {
      std::cout << square << " 0x" << std::hex << magic << std::dec << "ULL, " << usedCount << " " << variationCount << std::endl;
    }
    // std::cout << "0x" << std::hex << magic << "ULL," << std::dec << std::endl;
    magics.push_back(magic);
  }
  return magics;
}
