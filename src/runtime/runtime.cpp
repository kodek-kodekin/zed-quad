#include <runtime.hpp>

uint64_t bytes_to_64(uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4, uint8_t b5, uint8_t b6, uint8_t b7, uint8_t b8) {
    uint64_t res = b1 | (b2 << 8) | (b3 << 16) | (b4 << 24) | (b5 << 32) | (b6 << 40) | (b7 << 48) | (b8 << 56);
    return res;
}

z4::VContext::VContext(uint8_t* file, uint64_t size) {
    
}