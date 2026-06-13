#include <comptime/comptime.hpp>

using namespace z4;

enum class MathOperator : uint8_t {
    Plus,
    Minus,
    Divide,
    Multiple
};

struct MathEntry {
    int64_t first;
    int64_t second;
    MathOperator op;
};

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
            
            argname = argname.token('\t', true);
            argname = argname.token(' ', true);
            
            String argtypes = arg.token(',');
            
            argtypes = argtypes.token('\t', true);
            argtypes = argtypes.token(' ', true);
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
        
        rettypes = rettypes.token('\t', true);
        rettypes = rettypes.token(' ', true);
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
        
        write.is_empty = 0;
        if(!instr.is_valid()) write.is_empty = 1;
        
    } else if (first_word == "let") {
        VarEntry write;
        
        write.offset = _var_counter;
        ++_var_counter;
        
        String name = clear.token(':');
        name = name.token('\t', true);
        name = name.token(' ', true);
        
        clear = clear.jump(':', true);
        if(!clear.is_valid()) //TODO: добавить ошибку
        
        String type = clear.token('=');
        type = type.stage_void();
        type = type.token('\t');
        type = type.token(' ');
        
        if(type.match("void")) {
            //TODO: добавить ошибку
        } else if(type.match("int")) {
            write.type = VarTypes::Int;
        } //TODO: доьавить другие типы
        
        String svin = clear.jump('=', true);
        
        svin = svin.token('\n');
        svin = svin.stage_void();
        svin = svin.token(' ', true);
        svin = svin.token('\t', true);
        
        if(svin.match('(', 1)) {
            //арифметический код
        } else if(_vars.find(svin.token('\n'))) {
            
        }
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