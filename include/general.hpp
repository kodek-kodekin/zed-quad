#pragma once

typedef int64_t vm_slot;

namespace z4 {
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