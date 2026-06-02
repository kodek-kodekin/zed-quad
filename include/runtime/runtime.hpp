#pragma once

#include <general.hpp>

#if defined(Z4_BERSERK)

#define HEAP_SIZE 128
#define STACK_SIZE 128

#else

#define HEAP_SIZE 64
#define STACK_SIZE 64

#endif

namespace z4 {
    
    struct VContext {
        vm_slot stack[STACK_SIZE];
        vm_slot heap[HEAP_SIZE];
        
        uint8_t* btc_start;
        z4::AssembledState* state;
        
        #if defined(Z4_BERSERK)
        //TODO: добавить ватчдог
        uint8_t id;
        #endif
        
        VContext(uint8_t* file, uint64_t size);
        
        bool is_valid : 1;
    };
    
    class VMachine {
    private:
        #if defined(Z4_BERSERK)
        z4::VContext[10] scripts;
        #else
        z4::VContext script;
        #endif
        
        void execute_time(size_t ins);
        
    public:
        #if defined(Z4_BERSERK)
        VMachine(z4::VContext* context_arr, uint8_t arr_size);
        #else
        VMachine(z4::VContext context);
        #endif
        
        void exec(uint8_t flags);
    };
}