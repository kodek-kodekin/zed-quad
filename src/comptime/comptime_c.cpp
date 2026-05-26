#include <comptime.hpp>
#include <comptime_c.h>

using namespace z4;

extern "C" void* z4_assembler_init(uint8_t flags) {
    Assembler* obj = new Assembler(flags);
    return static_cast<void*>(obj);
}

extern "C" void z4_assembler_free(void* assembler) {
    if(assembler != nullptr) {
        Assembler* ptr = static_cast<Assembler*>(assembler);
        delete ptr;
    }
}

extern "C" void* z4_assemble(void* assembler) {
    
}