#include <comptime/comptime.hpp>

using namespace z4;

ParseResult Assembler::parse_str(String& str) {
    ParseResult res;
    res.btc.err = ParseError::None;
    
    String clear = str.stage_void();
    String first_word = clear.token(' ');
    
    if(first_word == "#debug") {
        res.note.op = AssembleCodes::FlagDebug;
        res.note.empty = false;
    } else if (first_word == "fn") {
        FuncEntry write;
        
        String name = clear.token('(');
        write.name = name;
        
        String args = clear.token(')');
        args = args.stage_up('(');
        
        for(int i = 0; i < 6; i++) {
            String arg = args.token(',');
            if(!arg.is_valid()) break;
            
            String argname = arg.token(':');
            String argtypes = arg.token(',');
            VarTypes argtype;
            
            if(argtypes == "void") {
                argtype = VarTypes::Void;
            } else if(argtypes == "int") {
                argtype = VarTypes::Int;
            } //TODO: доьавить другие типы
            
            write.args[i].name = argname;
            write.args[i].type = argtype;
        }
        String dual = clear.jump(':', true);
        if(!dual.is_valid()) //TODO: добавить ошибку
        
        String rettypes = dual.token('{');
        
        rettypes = rettypes.token('\t');
        rettypes = rettypes.token(' ');
        VarTypes rettype;
        
        if(rettypes == "void") {
            rettype = VarTypes::Void;
        } else if(rettypes == "int") {
            rettype = VarTypes::Int;
        } //TODO: добавить другие типы
        
        write.return_type = rettype;
        
        String body = clear.jump('{', true);
        body = body.token('}');
        
        String instr = body.token('\n');
        
        if(!instr.is_valid()) write.is_empty = 1;
    } else if (first_word == "let") {
        res.note.op = AssembleCodes::FlagDebug;
        res.note.empty = false;
    } else if (first_word == "struct") {
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