#pragma once

#include <cstdint>
#include <general.hpp>
#include <comptime/comptime_tools.hpp>
#include <comptime/symtabs.hpp

namespace z4 {
    enum class AssembleCodes : uint8_t {
        FlagDebug = 0,
        ValueWrite = 1,
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
        uint8_t _flags;
        
        uint8_t _fn_counter;
        uint8_t _var_counter;
        
        z4::ParseResult parse_str(String& str);
        
        //symtables
        Vec<z4::FuncEntry> _funcs;
        Vec<z4::VarEntry> _vars;
    public:
        Assembler(flags) : _flags(flags), _fn_counter(0), _var_counter(0) {}
        
        Assembler(const Assembler& other) = delete;
        Assembler& operator=(const Assembler& other) = delete;
        
        z4::AssembledState assemble(uint64_t* data_s, uint8_t* code_s, Vec<String>& strs);
    }; //class Assembler
}