#ifndef GRAPHHW1_H
#define GRAPHHW1_H
#include "bitset.h"
#include "mloccpy.h"

// Definition of a single node in the queue; it stores a data pointer and a link to the next node.
struct object{
    void* key;
    struct object* next;
    struct object* prev;
};
typedef struct object obj;

// Maximum number of priority levels
#define L_SIZE 10000

// Initialize the whole queue array so that all are empty.
int initQ(obj* list);

// Insert a new element with given priority and data size into the queue.
int insertQ(obj* list, void* data, int priority, int data_size);

// Remove and return one element from the queue according to priority and FIFO order inside that priority.
void* deleteQ(obj* list);

#endif
