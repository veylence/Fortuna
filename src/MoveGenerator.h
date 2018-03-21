
#ifndef MOVEGENERATOR_H_
#define MOVEGENERATOR_H_

#include <vector>

#include "Types.h"
#include "GenerateMagics.h"

namespace MoveGen {
// How many 1 bits in the occupancy mask of a rook on some square.
// Used to compute an index for magic bitboards.
const int MAGIC_NUMBER_SHIFTS_ROOK[] = {
    52, 53, 53, 53, 53, 53, 53, 52,
    53, 54, 54, 54, 54, 54, 54, 53,
    53, 54, 54, 54, 54, 54, 54, 53,
    53, 54, 54, 54, 54, 54, 54, 53,
    53, 54, 54, 54, 54, 54, 54, 53,
    53, 54, 54, 54, 54, 54, 54, 53,
    53, 54, 54, 54, 54, 54, 54, 53,
    52, 53, 53, 53, 53, 53, 53, 52
};

// How many 1 bits in the occupancy mask of a bishop on some square.
// Used to compute an index for magic bitboards.
const int MAGIC_NUMBER_SHIFTS_BISHOP[] = {
    58, 59, 59, 59, 59, 59, 59, 58,
    59, 59, 59, 59, 59, 59, 59, 59,
    59, 59, 57, 57, 57, 57, 59, 59,
    59, 59, 57, 55, 55, 57, 59, 59,
    59, 59, 57, 55, 55, 57, 59, 59,
    59, 59, 57, 57, 57, 57, 59, 59,
    59, 59, 59, 59, 59, 59, 59, 59,
    58, 59, 59, 59, 59, 59, 59, 58
};

// Rook occupancy masks for each square
const U64 OCCUPANCY_MASKS_ROOK[] = {
    0x101010101017eULL,    0x202020202027cULL,    0x404040404047aULL,    0x8080808080876ULL,
    0x1010101010106eULL,   0x2020202020205eULL,   0x4040404040403eULL,   0x8080808080807eULL,
    0x1010101017e00ULL,    0x2020202027c00ULL,    0x4040404047a00ULL,    0x8080808087600ULL,
    0x10101010106e00ULL,   0x20202020205e00ULL,   0x40404040403e00ULL,   0x80808080807e00ULL,
    0x10101017e0100ULL,    0x20202027c0200ULL,    0x40404047a0400ULL,    0x8080808760800ULL,
    0x101010106e1000ULL,   0x202020205e2000ULL,   0x404040403e4000ULL,   0x808080807e8000ULL,
    0x101017e010100ULL,    0x202027c020200ULL,    0x404047a040400ULL,    0x8080876080800ULL,
    0x1010106e101000ULL,   0x2020205e202000ULL,   0x4040403e404000ULL,   0x8080807e808000ULL,
    0x1017e01010100ULL,    0x2027c02020200ULL,    0x4047a04040400ULL,    0x8087608080800ULL,
    0x10106e10101000ULL,   0x20205e20202000ULL,   0x40403e40404000ULL,   0x80807e80808000ULL,
    0x17e0101010100ULL,    0x27c0202020200ULL,    0x47a0404040400ULL,    0x8760808080800ULL,
    0x106e1010101000ULL,   0x205e2020202000ULL,   0x403e4040404000ULL,   0x807e8080808000ULL,
    0x7e010101010100ULL,   0x7c020202020200ULL,   0x7a040404040400ULL,   0x76080808080800ULL,
    0x6e101010101000ULL,   0x5e202020202000ULL,   0x3e404040404000ULL,   0x7e808080808000ULL,
    0x7e01010101010100ULL, 0x7c02020202020200ULL, 0x7a04040404040400ULL, 0x7608080808080800ULL,
    0x6e10101010101000ULL, 0x5e20202020202000ULL, 0x3e40404040404000ULL, 0x7e80808080808000ULL
};

// Bishop occupancy masks for each square
const U64 OCCUPANCY_MASKS_BISHOP[] = {
    0x40201008040200ULL, 0x402010080400ULL,   0x4020100a00ULL,     0x40221400ULL,
    0x2442800ULL,        0x204085000ULL,      0x20408102000ULL,    0x2040810204000ULL,
    0x20100804020000ULL, 0x40201008040000ULL, 0x4020100a0000ULL,   0x4022140000ULL,
    0x244280000ULL,      0x20408500000ULL,    0x2040810200000ULL,  0x4081020400000ULL,
    0x10080402000200ULL, 0x20100804000400ULL, 0x4020100a000a00ULL, 0x402214001400ULL,
    0x24428002800ULL,    0x2040850005000ULL,  0x4081020002000ULL,  0x8102040004000ULL,
    0x8040200020400ULL,  0x10080400040800ULL, 0x20100a000a1000ULL, 0x40221400142200ULL,
    0x2442800284400ULL,  0x4085000500800ULL,  0x8102000201000ULL,  0x10204000402000ULL,
    0x4020002040800ULL,  0x8040004081000ULL,  0x100a000a102000ULL, 0x22140014224000ULL,
    0x44280028440200ULL, 0x8500050080400ULL,  0x10200020100800ULL, 0x20400040201000ULL,
    0x2000204081000ULL,  0x4000408102000ULL,  0xa000a10204000ULL,  0x14001422400000ULL,
    0x28002844020000ULL, 0x50005008040200ULL, 0x20002010080400ULL, 0x40004020100800ULL,
    0x20408102000ULL,    0x40810204000ULL,    0xa1020400000ULL,    0x142240000000ULL,
    0x284402000000ULL,   0x500804020000ULL,   0x201008040200ULL,   0x402010080400ULL,
    0x2040810204000ULL,  0x4081020400000ULL,  0xa102040000000ULL,  0x14224000000000ULL,
    0x28440200000000ULL, 0x50080402000000ULL, 0x20100804020000ULL, 0x40201008040200ULL
};

// Magic numbers for each square for rooks.
// Used to compute an index for magic bitboards.
const U64 MAGIC_NUMBERS_ROOKS[] = {
    0x80104000608000ULL,
    0x80102000400080ULL,
    0x1000c1100200040ULL,
    0x80048010001800ULL,
    0x8480040028008002ULL,
    0x80020080014400ULL,
    0x1480050000802600ULL,
    0x200004100802402ULL,
    0x201002080010044ULL,
    0x8040400040201000ULL,
    0x4001001020044100ULL,
    0x1a0801000800800ULL,
    0x8802400800800ULL,
    0x8002800400800200ULL,
    0x800800100801200ULL,
    0x80800100004080ULL,
    0x80808000400020ULL,
    0xc44000601000ULL,
    0x480910020030440ULL,
    0x30808010000800ULL,
    0x48008028800400ULL,
    0x8808002000400ULL,
    0x840001084210ULL,
    0x20000440189ULL,
    0x22208080084000ULL,
    0x400080200080ULL,
    0x4a00080100080ULL,
    0x2041080080801000ULL,
    0x8000240280180080ULL,
    0x9040080020080ULL,
    0x1c0101000200ULL,
    0x48200004104ULL,
    0x400020800084ULL,
    0x40062004804180ULL,
    0x80a000801000ULL,
    0x10801001800800ULL,
    0x88020040400400ULL,
    0x20440080800200ULL,
    0x800100800200ULL,
    0x41000081000042ULL,
    0x80004120124000ULL,
    0x4004500020004004ULL,
    0x6200010008080ULL,
    0x100210010050018ULL,
    0x10080004008080ULL,
    0x200440880110ULL,
    0x3200040200030100ULL,
    0x602010080420004ULL,
    0x80800020400080ULL,
    0x400882a008400080ULL,
    0x20200c08210a200ULL,
    0x1800080082100080ULL,
    0x80040080080180ULL,
    0x9020800400020080ULL,
    0x200081c014200ULL,
    0x8100640200ULL,
    0x104100208001ULL,
    0x101802108104001ULL,
    0x1002000400815ULL,
    0x2082100100005ULL,
    0x802014810200402ULL,
    0x421000204000801ULL,
    0x8010004008a0021ULL,
    0x140081024022ULL
};

// Magic numbers for each square for bishops.
// Used to compute an index for magic bitboards.
const U64 MAGIC_NUMBERS_BISHOPS[] = {
    0x40100080810044ULL,
    0x10010200820000ULL,
    0x4004040082000000ULL,
    0x4040080000000ULL,
    0x4042040000010ULL,
    0x9018840004204ULL,
    0x1480210100000ULL,
    0x802802801042000ULL,
    0x40408080100ULL,
    0x100202024200ULL,
    0x4180800408000ULL,
    0x424081000000ULL,
    0x11040000040ULL,
    0x20104200000ULL,
    0x40401880800ULL,
    0x4100901000ULL,
    0x40810a0082103ULL,
    0x2004021010020040ULL,
    0x1009004002040ULL,
    0x8000082004000ULL,
    0x40002010c0000ULL,
    0x200040120100a000ULL,
    0x20200008a100200ULL,
    0x40800024010800ULL,
    0x4400010020804ULL,
    0x20c020010300900ULL,
    0x124021810008014ULL,
    0x40100812008010ULL,
    0x1009101004000ULL,
    0x10010000808080ULL,
    0x8020080040c0100ULL,
    0xa008400208800ULL,
    0x30901004080210ULL,
    0x821004081002ULL,
    0x4020800010040ULL,
    0x2001201100080084ULL,
    0x404040040100ULL,
    0x14008200208800ULL,
    0x10040080010080ULL,
    0x2020200004040ULL,
    0x4010440021000ULL,
    0x1080104001100ULL,
    0x8101008050000102ULL,
    0x2500010280800800ULL,
    0x80002200a000100ULL,
    0x2004018482000100ULL,
    0x10100101200040ULL,
    0x10008080800100ULL,
    0x80808820100000ULL,
    0x904402200040ULL,
    0x14404040000ULL,
    0x4000042084040000ULL,
    0x4020021012020000ULL,
    0x400408008000ULL,
    0xa089004004880ULL,
    0x450100083004000ULL,
    0xa20802011000ULL,
    0x1108404880400ULL,
    0x108411000ULL,
    0x1000000008208800ULL,
    0x10020600ULL,
    0x44008010100ULL,
    0x80808008400ULL,
    0x10200801004010ULL
};

// King move table
const U64 KING_MOVES[] = {
    0x0000000000000302L, 0x0000000000000705L, 0x0000000000000e0aL,
    0x0000000000001c14L, 0x0000000000003828L, 0x0000000000007050L,
    0x000000000000e0a0L, 0x000000000000c040L, 0x0000000000030203L,
    0x0000000000070507L, 0x00000000000e0a0eL, 0x00000000001c141cL,
    0x0000000000382838L, 0x0000000000705070L, 0x0000000000e0a0e0L,
    0x0000000000c040c0L, 0x0000000003020300L, 0x0000000007050700L,
    0x000000000e0a0e00L, 0x000000001c141c00L, 0x0000000038283800L,
    0x0000000070507000L, 0x00000000e0a0e000L, 0x00000000c040c000L,
    0x0000000302030000L, 0x0000000705070000L, 0x0000000e0a0e0000L,
    0x0000001c141c0000L, 0x0000003828380000L, 0x0000007050700000L,
    0x000000e0a0e00000L, 0x000000c040c00000L, 0x0000030203000000L,
    0x0000070507000000L, 0x00000e0a0e000000L, 0x00001c141c000000L,
    0x0000382838000000L, 0x0000705070000000L, 0x0000e0a0e0000000L,
    0x0000c040c0000000L, 0x0003020300000000L, 0x0007050700000000L,
    0x000e0a0e00000000L, 0x001c141c00000000L, 0x0038283800000000L,
    0x0070507000000000L, 0x00e0a0e000000000L, 0x00c040c000000000L,
    0x0302030000000000L, 0x0705070000000000L, 0x0e0a0e0000000000L,
    0x1c141c0000000000L, 0x3828380000000000L, 0x7050700000000000L,
    0xe0a0e00000000000L, 0xc040c00000000000L, 0x0203000000000000L,
    0x0507000000000000L, 0x0a0e000000000000L, 0x141c000000000000L,
    0x2838000000000000L, 0x5070000000000000L, 0xa0e0000000000000L,
    0x40c0000000000000L
};

// Knight move table
const U64 KNIGHT_MOVES[] = {
    0x0000000000020400L, 0x0000000000050800L, 0x00000000000a1100L,
    0x0000000000142200L, 0x0000000000284400L, 0x0000000000508800L,
    0x0000000000a01000L, 0x0000000000402000L, 0x0000000002040004L,
    0x0000000005080008L, 0x000000000a110011L, 0x0000000014220022L,
    0x0000000028440044L, 0x0000000050880088L, 0x00000000a0100010L,
    0x0000000040200020L, 0x0000000204000402L, 0x0000000508000805L,
    0x0000000a1100110aL, 0x0000001422002214L, 0x0000002844004428L,
    0x0000005088008850L, 0x000000a0100010a0L, 0x0000004020002040L,
    0x0000020400040200L, 0x0000050800080500L, 0x00000a1100110a00L,
    0x0000142200221400L, 0x0000284400442800L, 0x0000508800885000L,
    0x0000a0100010a000L, 0x0000402000204000L, 0x0002040004020000L,
    0x0005080008050000L, 0x000a1100110a0000L, 0x0014220022140000L,
    0x0028440044280000L, 0x0050880088500000L, 0x00a0100010a00000L,
    0x0040200020400000L, 0x0204000402000000L, 0x0508000805000000L,
    0x0a1100110a000000L, 0x1422002214000000L, 0x2844004428000000L,
    0x5088008850000000L, 0xa0100010a0000000L, 0x4020002040000000L,
    0x0400040200000000L, 0x0800080500000000L, 0x1100110a00000000L,
    0x2200221400000000L, 0x4400442800000000L, 0x8800885000000000L,
    0x100010a000000000L, 0x2000204000000000L, 0x0004020000000000L,
    0x0008050000000000L, 0x00110a0000000000L, 0x0022140000000000L,
    0x0044280000000000L, 0x0088500000000000L, 0x0010a00000000000L,
    0x0020400000000000L
};

// Rook magic bitboard move table
extern U64* ROOK_MOVES[Square::SQ_NUM];
// Bishop magic bitboard move table
extern U64* BISHOP_MOVES[Square::SQ_NUM];

/**
 * Initializes the rook and bishop magic bitboard move tables.
 */
void init();

U64 genKnightMoves(U64 piece, U64 myBoard);
U64 genKingMoves(U64 piece, U64 myBoard);
}

#endif /* MOVEGENERATOR_H_ */
