#define EXSTD_ALLOC
#include "exstd.h"

void* h_allocninit(usize size, const void* init_val){
    void* alloced = malloc(size);
    if (!alloced){
        return NULL;
    }
    memcpy(alloced, init_val, size);
    return alloced;
}