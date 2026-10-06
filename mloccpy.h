#ifndef MLOCCPY_H
#define MLOCCPY_H

//==============================
// Memory Management Functions
//==============================

// Allocate memory from the fixed-size pool
// Parameters: size - number of bytes to allocate
// Returns: pointer to allocated memory, or NULL if pool is full
void* mloc(int size);

// Copy memory from source to destination
// Parameters: dest - destination pointer, src - source pointer, size - bytes to copy
void mcpy(void* dest, void* src, int size);
//==============================

#endif
