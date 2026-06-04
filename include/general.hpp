#pragma once

#include <cstdint>

typedef int64_t vm_slot;

namespace z4 {
    
    #pragma pack(push, 1)
    struct AssembledState {
        uint32_t magic;
        uint16_t code_start;
        vm_slot separ[100];
        vm_slot rtpredictor[100];
        vm_slot fns[40];
        
        AssembledState(uint8_t* file) {
            uint8_t b1, b2, b3, b4 = 0;
    
            b1 = file[0];
            b2 = file[1];
            b3 = file[2];
            b4 = file[3];
    
            uint32_t res = b1 | (b2) << 8) | (b3 << 16) | (b4 << 24);
    
            if(!res == ZED4_MAGIC) {
                self.is_valid = 0;
                return;
            }
    
    self.is_valid = 1;
        }
    }; //struct AssembledState
    #pragma pack(pop)
    
    enum class RuntimeCodes : uint8_t {
        None = 0,
        Load,
        LoadExt,
        LoadStruct,
    };
    
    #define ZED4_MAGIC 0x5A656434
    #define SEPAR_START (0)
    #define B_SEPAR_START (32 + 16 + 1)
    #define RTPREDICTOR_START (SEPAR_START + 255 + 1)
    #define FNS_START (RTPREDICTOR_START + 40 + 1)
}