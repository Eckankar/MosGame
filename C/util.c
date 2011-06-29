#include "general.h"
#include "util.h"

// Converts a pointer to a ML value.
// 
// Assumes that the pointer is alligned to a word boundary, and that the word
// size is a multiple of 2.
value Val_addr(void* addr) {
    return (long)addr + 1;
}

void* Addr_val(value val) {
    return (void*)(val - 1);
}

