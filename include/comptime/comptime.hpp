#pragma once

#include <cstdint>
#include <comptime/comptime_tools.hpp>

namespace z4 {
    #define DATA_SZ (255 + 255 + 40)
    #define ZED4_MAGIC 0x5A656434
    #define SEPAR_START (0)
    #define RTPREDICTOR_START (SEPAR_START + 255)
    #define FNS_START (RTPREDICTOR_START + 40)

    #pragma pack(push, 1)
    struct AssembledState {
        struct {
            uint32_t magic;
            uint16_t code_start;
            uint64_t code_size;
            uint16_t separ_start;
            uint16_t rtpredictor_start;
            uint16_t fns_start;
        } header;
        uint64_t data[DATA_SZ];
    }; //struct AssembledState
    #pragma pack(pop)
    
    enum class AssembleCodes : uint8_t {
        FlagDebug = 0
    };
    
    enum class ParseError : uint8_t {
        None = 0,
        UnknownCommand
    };
    
    struct ParseResult {
        struct {
            uint64_t data;
            uint64_t second_data;
            AssembleCodes code;
            bool empty: 1;
        } note;
        struct {
            Vec<uint8_t> bytes;
            ParseError err;
        } btc;
    }; //struct ParseResult
    
    class Assembler {
    private:
        AssembledState _asm_state;
        uint8_t _flags;
        
        ParseResult parse_str(String& str);
        Vec<String> _text;
    public:
        Assembler(flags) : _flags(flags), _iflags(0), _asm_state{}, _bytecode(20) {}
        
        Assembler(const Assembler& other) = delete;
        Assembler& operator=(const Assembler& other) = delete;
        
        AssembledState assemble(uint64_t* data_s, uint8_t* code_s, Vec<String>& strs);
    }; //class Assembler
}