#include <comptime/comptime.hpp>

using namespace z4;

ParseResult Assembler::parse_str(String& str) {
    ParseResult res;
    res.btc.err = ParseError::None;
    
    String first_word = str.token(' ');
    
    if(first_word == "#debug") {
        res.note.op = AssembleCodes::FlagDebug;
        res.note.empty = false;
    }
}

#define IFLAGS_DEBUG 0x01

AssembledState Assembler::assemble(uint64_t* data_s, ssize_t data_size, uint8_t* code_s, Vec<String>& strs) {
    
    AssembledState state{};
    
    for(size_t i = 0; i < strs.get_capacity(); i++) {
        ParseResult parsed = parse_str(strs[i]);
        
        size_t filled = 0;
        
        while(data_size > 8 || parsed.bytes.get_size() > 8) {
            memcpy(data_s + filled, parsed.bytes[filled], 8);
        }
        
        if(parsed.note.empty != false) {
            switch(parsed.note.op) {
                case AssembleCodes::FlagDebug: {
                    self._iflags |= IFLAGS_DEBUG;
                    break;
                }
                default: break;
            }
        }
    }
}