#pragma once

#include <comptime/comptime_tools.hpp>
#include <comptime/types.hpp>

namespace z4 {
    struct FuncEntry {
        struct FnArg {
            String name;
            z4::VarTypes type;
            
            FnArg(): name(""), type(z4::VarTypes::Void) {}
        } args[6];
        
        String name;
        z4::VarTypes return_type;
        bool is_empty : 1;
    };
    
    struct VarEntry {
        String name;
        int offset;
        z4::VarTypes type;
        
        bool is_blockaded : 1;
    };
}