#include "bitset.h"
#include <stddef.h>

int pri_exists[L_SIZE]={0};
unsigned int pri_bits[WORD_COUNT];
unsigned int word_summary = 0;
unsigned char lsb_table[256];

// Build a lookup table for the least significant set bit position for all 8‑bit values 1..255.
void build_lsb_table() {
    int i;
    for (i = 1; i < 256; i++) {
        unsigned char v = (unsigned char)i;  // Current value whose LSB position we are finding.
        unsigned char pos = 0;               // Position counter for the least significant set bit.
        while ((v & 1u) == 0u) {             // Shift right until the lowest bit becomes 1.
            v >>= 1;
            pos++;
        }
        lsb_table[i] = pos;                  // Store the position for this value.
    }
}

// Mark a priority p as present by setting its bit in pri_bits and updating word_summary.
void set_priority_bit(int p) {
    int word = p / WORD_BITS;               // Index of the word that contains bit p.
    int bit  = p % WORD_BITS;               // Bit position inside that word.
    unsigned int mask = 1u << bit;          // Mask with a 1 at the bit position.

    // Only update if the bit is currently 0.
    if ((pri_bits[word] & mask) == 0u) {
        pri_bits[word] |= mask;             // Set the bit to indicate this priority exists.
        if (pri_bits[word] != 0u) {
            // Mark that this word has at least one bit set.
            word_summary |= (1u << word);
        }
    }
}


// Clear the bit for priority p when the corresponding bucket becomes empty.
void clear_priority_bit(int p) {
    int word = p / WORD_BITS;               // Index of the word that contains bit p.
    int bit  = p % WORD_BITS;               // Bit position inside that word.
    unsigned int mask = 1u << bit;          // Mask for that bit.

    if ((pri_bits[word] & mask) != 0u) {    // Only modify if the bit is currently set.
        pri_bits[word] &= ~mask;            // Clear the bit for this priority.
        if (pri_bits[word] == 0u) {
            // If this word has become all zeros, clear its bit in the summary mask.
            word_summary &= ~(1u << word);
        }
    }
}

// Find the smallest priority that currently exists using the summary and lsb_table.
int find_min_priority() {
    if (word_summary == 0u) return -1;      // No priorities exist at all.

    // Split word_summary into 4 bytes to find the least significant non‑zero byte.
    unsigned char b0 = (unsigned char)( word_summary        & 0xFFu );
    unsigned char b1 = (unsigned char)((word_summary >> 8)  & 0xFFu );
    unsigned char b2 = (unsigned char)((word_summary >> 16) & 0xFFu );
    unsigned char b3 = (unsigned char)((word_summary >> 24) & 0xFFu );

    int word_index = 0;                     // Index of the word that contains the smallest set bit.
    if (b0 != 0u) {
        word_index = lsb_table[b0];         // The first non‑zero byte is b0.
    } else if (b1 != 0u) {
        word_index = 8  + lsb_table[b1];    // Byte b1 corresponds to bits 8..15.
    } else if (b2 != 0u) {
        word_index = 16 + lsb_table[b2];    // Byte b2 corresponds to bits 16..23.
    } else {        // b3 != 0
        word_index = 24 + lsb_table[b3];    // Byte b3 corresponds to bits 24..31.
    }

    // Now look inside the specific pri_bits word to find the exact bit position.
    unsigned int w = pri_bits[word_index];  // The word that has the smallest active priority.
    unsigned char c0 = (unsigned char)( w        & 0xFFu );
    unsigned char c1 = (unsigned char)((w >> 8)  & 0xFFu );
    unsigned char c2 = (unsigned char)((w >> 16) & 0xFFu );
    unsigned char c3 = (unsigned char)((w >> 24) & 0xFFu );

    int bit_index = 0;                      // Bit index inside this word.
    if (c0 != 0u) {
        bit_index = lsb_table[c0];
    } else if (c1 != 0u) {
        bit_index = 8  + lsb_table[c1];
    } else if (c2 != 0u) {
        bit_index = 16 + lsb_table[c2];
    } else {        // c3 != 0
        bit_index = 24 + lsb_table[c3];
    }

    // Global priority = word_index * bits_per_word + bit_index inside that word.
    return word_index * WORD_BITS + bit_index;
}
