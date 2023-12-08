#include <stdint.h>
#include <stdio.h>


// Define a macro to check the system endianness
#define IS_LITTLE_ENDIAN (*(uint16_t *)"\0\xff" > 0xFF)

// Function to swap endianness of a 16-bit integer
uint16_t swap_endian_16(uint16_t value) {
    return (value << 8) | (value >> 8);
}

// Function to swap endianness of a 32-bit integer
uint32_t swap_endian_32(uint32_t value) {
    return ((value << 24) & 0xFF000000) |
           ((value << 8) & 0x00FF0000) |
           ((value >> 8) & 0x0000FF00) |
           ((value >> 24) & 0x000000FF);
}

// Function to swap endianness of a 64-bit integer
uint64_t swap_endian_64(uint64_t value) {
    return ((value << 56) & 0xFF00000000000000ULL) |
           ((value << 40) & 0x00FF000000000000ULL) |
           ((value << 24) & 0x0000FF0000000000ULL) |
           ((value << 8)  & 0x000000FF00000000ULL) |
           ((value >> 8)  & 0x00000000FF000000ULL) |
           ((value >> 24) & 0x0000000000FF0000ULL) |
           ((value >> 40) & 0x000000000000FF00ULL) |
           ((value >> 56) & 0x00000000000000FFULL);
}

// Function to write data to binary format
void write_binary(FILE *file, const void *data, size_t size) {
    fwrite(data, 1, size, file);
}

// Function to read data from binary format
void read_binary(FILE *file, void *data, size_t size) {
    fread(data, 1, size, file);
}

int main() {
    // Example usage:

    // Write a 32-bit integer to a binary file
    uint32_t originalValue = 0x12345678;
    FILE *writeFile = fopen("binary_data.bin", "wb");
    if (writeFile != NULL) {
        if (IS_LITTLE_ENDIAN) {
            originalValue = swap_endian_32(originalValue);
        }
        write_binary(writeFile, &originalValue, sizeof(originalValue));
        fclose(writeFile);
    }

    // Read the 32-bit integer from the binary file
    uint32_t readValue = 0;
    FILE *readFile = fopen("binary_data.bin", "rb");
    if (readFile != NULL) {
        read_binary(readFile, &readValue, sizeof(readValue));
        fclose(readFile);
    }

    // Convert back to the original endianness if necessary
    if (IS_LITTLE_ENDIAN) {
        readValue = swap_endian_32(readValue);
    }

    // Print the result
    printf("Original Value: 0x%08X\n", originalValue);
    printf("Read Value:     0x%08X\n", readValue);

    return 0;
}
