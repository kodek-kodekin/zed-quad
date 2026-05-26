#pragma once
#include <stdint.h>

//file for C and other laungages

void* z4_assembler_init(uint8_t flags);
void z4_assembler_free(void* assembler);

void* z4_assembler_parse(void* assembler);