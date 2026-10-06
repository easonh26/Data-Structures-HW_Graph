#ifndef GRAPHHWLOGN_H
#define GRAPHHWLOGN_H
#include "minheap.h"

// Definition of a single node in the queue; it stores a data pointer and a link to the next node.
struct object{
	minhp* hp;
	void* key;
	struct object* next;
	struct object* prev;
};
typedef struct object obj;

// Maximum number of priority levels
#define L_SIZE 10000

extern int pri_exists[L_SIZE];

// Initialize the whole queue array so that all are empty.
int initQ(obj* list);

// Insert a new element with given priority and data size into the queue.
int insertQ(obj* list, void* data, int priority, int data_size, int compare(void*, void*));

// Remove and return one element from the queue according to priority and FIFO order inside that priority.
void* deleteQ(obj* list, int compare(void*, void*));


#endif
