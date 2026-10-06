#include "mloccpy.h"
#include <stddef.h>

// ============================
// Memory Pool Management
// ============================

// Static memory pool - fixed 100KB for all allocations
char memory_pool[100000];
// Current position in memory pool
int pool_index=0;

// Simple memory allocation from fixed pool
// If pool is full, returns NULL
void* mloc(int size) {
    if (pool_index+size>100000) {
        return (void*)0;  
    }
    void* ptr=(void*)(&memory_pool[pool_index]);
    pool_index+=size;
    return ptr;
}

// Copy data from source to destination
// Uses byte-by-byte copy (equivalent to memcpy)
void mcpy(void* dest, void* src, int size) {
    char* d=(char*)dest;
    char* s=(char*)src;
    for (int i=0; i<size; i++) {
        d[i]=s[i];
    }
}

