#ifndef MINHEAP_H
#define MINHEAP_H

struct minheap{
	void** data;
	int size;
	int cap;
};
typedef struct minheap minhp;

// Initialize a heap with a given capacity
int minhp_init(minhp* m, int cap);

// Move a node up the heap until the min-heap property is satisfied.
int minhp_in(minhp* m, int index, int compare(void*, void*));

// Insert a new element
int minhp_push(minhp* m, void* data, int compare(void*, void*));

// Move a node down the heap until the min-heap property is satisfied.
int minhp_out(minhp* m, int index, int compare(void*, void*));

// Remove the smallest element from the heap.
int minhp_pop(minhp* m, int compare(void*, void*));

// Return the smallest element in the heap
void* minhp_top(minhp* m);


#endif

