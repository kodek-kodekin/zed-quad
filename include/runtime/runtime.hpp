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
        z4::vm_slot stack[STACK_SIZE];
        z4::vm_slot heap[HEAP_SIZE];
        
        uint8_t* btc_start;
        
        #if defined(Z4_BERSERK)
        //TODO: добавить ватчдог
        uint8_t id;
        #endif
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