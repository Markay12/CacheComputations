#include <stdio.h>
#include <stdlib.h>

int main() {
    unsigned int memory_address;
    unsigned int cache_size, block_size;
    unsigned int num_cache_lines, words_per_block, tag_bits, block_offset_bits, byte_offset_bits, word_offset_bits;

    // Prompt the user for the memory address
    printf("Enter memory address (in hexadecimal): ");
    scanf("%x", &memory_address);

    // Prompt the user for the cache size and block size
    printf("Enter cache size (in bytes): ");
    scanf("%u", &cache_size);
    printf("Enter block size (in bytes): ");
    scanf("%u", &block_size);

    // Calculate cache configuration parameters
    num_cache_lines = cache_size / (block_size * 4);   // Assuming 4 bytes per word
    words_per_block = block_size / 4;   // Assuming 4 bytes per word
    block_offset_bits = 0;
    while ((1 << block_offset_bits) < block_size) {
        block_offset_bits++;
    }
    byte_offset_bits = block_offset_bits - 2;
    word_offset_bits = 4;
    tag_bits = 32 - byte_offset_bits - word_offset_bits - block_offset_bits;

    // Calculate tag
    unsigned int tag = memory_address >> (block_offset_bits + byte_offset_bits + word_offset_bits);

    // Calculate memory block address
    unsigned int block_address = memory_address >> (byte_offset_bits + word_offset_bits);

    // Calculate cache block address/index
    unsigned int cache_index = (memory_address >> byte_offset_bits) & (num_cache_lines - 1);

    // Calculate block offset and word offset
    unsigned int block_offset = memory_address & (block_size - 1);
    unsigned int word_offset = block_offset / 4;

    // Print results
    printf("\nMemory address: 0x%08x\n", memory_address);
    printf("Cache configuration:\n");
    printf("  Cache size: %u bytes\n", cache_size);
    printf("  Block size: %u bytes\n", block_size);
    printf("  Number of cache lines: %u\n", num_cache_lines);
    printf("  Words per block: %u\n", words_per_block);
    printf("  Tag bits: %u\n", tag_bits);
    printf("  Block offset bits: %u\n", block_offset_bits);
    printf("  Byte offset bits: %u\n", byte_offset_bits);
    printf("  Word offset bits: %u\n", word_offset_bits);
    printf("Tag: 0x%0*x\n", tag_bits / 4, tag);
    printf("Memory block address: 0x%0*x\n", (block_offset_bits + byte_offset_bits + word_offset_bits) / 4, block_address);
    printf("Cache block address/index: %u\n", cache_index);
    printf("Block offset: 0x%x\n", block_offset);
    printf("Word offset: %u\n", word_offset);

    return 0;
}

