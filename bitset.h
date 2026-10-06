#ifndef BITSET_H
#define BITSET_H

// Maximum number of different priority values the queue supports.
#define L_SIZE 10000

// Record whether each priority currently exists in the queue (1 = exists, 0 = not used).
extern int pri_exists[L_SIZE];


// Maximum priority value supported by the bitset.
#define MAXP 1024
// Number of bits in one unsigned int.
#define WORD_BITS 32
// Number of unsigned int words needed to cover MAXP bits.
#define WORD_COUNT (MAXP / WORD_BITS)


// Bit array: each bit represents whether a given priority has at least one element.
extern unsigned int pri_bits[WORD_COUNT];

// Summary mask: each bit represents whether the corresponding word in pri_bits is non‑zero.
extern unsigned int word_summary;

// Lookup table: for any non‑zero 8‑bit value, gives the index of its least significant set bit.
extern unsigned char lsb_table[256];

// Precompute lsb_table so we can quickly find the least significant set bit in a byte.
void build_lsb_table();

// Mark that priority p exists (set the corresponding bit in pri_bits and word_summary).
void set_priority_bit(int p);

// Clear the bit for priority p when that priority bucket becomes empty.
void clear_priority_bit(int p);

// Return the smallest priority that currently exists, or -1 if none exist.
int find_min_priority();

#endif
